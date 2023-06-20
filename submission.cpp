#include <cstdlib>

#include "../state/state.hpp"
#include "./submission.hpp"


/**
 * @brief Randomly get a legal action
 *
 * @param state Now state
 * @param depth You may need this for other policy
 * @return Move
 */
Move ABP::get_move(State* state, int depth) {
    if (!state->legal_actions.size())
        state->get_legal_actions();

    auto actions = state->legal_actions;
    long unsigned int max_id = 0; 
    int max_val = -100000;
    int alpha = -100000, beta = 100000;
    for (long unsigned int i = 0; i < actions.size(); i++) {
        State* state_temp = state->next_state(actions[i]);
        int temp_val = abp(state_temp, depth-1, false, alpha, beta);
        if (temp_val > max_val) {
            max_val = temp_val;
            max_id = i;
        }
        if (max_val > alpha) {
            alpha = max_val;
        }
    }
    return actions[(int)max_id];
}

int ABP::abp(State* state, int depth, bool max_player, int alpha, int beta) {
    if (max_player) {
        if (!state->legal_actions.size())
            state->get_legal_actions();
        if (depth < 1) {
            return state->evaluate();
        }
        if (state->game_state == WIN) {
            return state->evaluate() + 100;
        }
        
        auto actions = state->legal_actions;
        int max_val = -100000;

        for (long unsigned int i = 0; i < actions.size(); i++) {
            State* state_temp = state->next_state(actions[i]);
            int temp_val = abp(state_temp, depth-1, false, alpha, beta);
            if (temp_val > max_val) {
                max_val = temp_val;
            }
            if (max_val > alpha) {
                alpha = max_val;
            }
            if (alpha >= beta) {
                break;
            }
        }
        return max_val;
    }
    else {
        if (!state->legal_actions.size())
            state->get_legal_actions();
        State* state2 = new State(state->board, 1-state->player);
        if (depth < 1) {
            return state2->evaluate();
        }
        if (state->game_state == WIN) {
            return state2->evaluate() - 100;
        }
        
        auto actions = state->legal_actions;

        int min_val = 100000;
        for (long unsigned int i = 0; i < actions.size(); i++) {
            State* state_temp = state->next_state(actions[i]);
            int temp_val = abp(state_temp, depth-1, true, alpha, beta);
            if (temp_val < min_val) {
                min_val = temp_val;
            }
            if (min_val < beta) {
                beta = min_val;
            }
            if (beta <= alpha) {
                break;
            }
        }
        return min_val;
    }
}