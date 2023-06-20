#pragma once
#include "../state/state.hpp"


/**
 * @brief Policy class for minimax policy,
 * your policy class should have get_move method
 */
class ABP {
public:
	static Move get_move(State* state, int depth);
	static int abp(State* state, int depth, bool max_player, int alpha, int beta);
};