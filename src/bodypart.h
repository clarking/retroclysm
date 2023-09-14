#pragma once

#include <string>

enum body_part {
	bp_head = 0,
	bp_eyes,
	bp_mouth,
	bp_torso,
	bp_arms,
	bp_hands,
	bp_legs,
	bp_feet,
	num_bp
};

std::string body_part_name(body_part bp, int side);

body_part random_body_part();

