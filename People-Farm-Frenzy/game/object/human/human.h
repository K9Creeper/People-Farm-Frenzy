#pragma once
#include <cstring>

#include <random>
#include <ctime>

#include "../object.h"
#include "../organ/organ.h"

/*
Todo:
	1. Create a unordered_map of textures for each human
*/

class Human : public GameObject {
public:
	double get_time_left() { return nAttributes["time_left"]; }
	bool get_exploded() { return nAttributes["exploded"]; }

	Organ drop_new_organ() {
		// Note: move to game loop
		std::srand(time(NULL));

		const double RANDOM = (double)(rand()) / (double)(RAND_MAX);
		Organ organ;
		if (RANDOM <= OrganChances[OrganType_Brain])
			organ.nAttributes["type"] = OrganType_Brain;
        if (RANDOM <= OrganChances[OrganType_Heart])
			organ.nAttributes["type"] = OrganType_Heart;
        if (RANDOM <= OrganChances[OrganType_Lung])
			organ.nAttributes["type"] = OrganType_Lung;
        if (RANDOM <= OrganChances[OrganType_Kidney])
			organ.nAttributes["type"] = OrganType_Kidney;
        if (RANDOM <= OrganChances[OrganType_Eyeball])
			organ.nAttributes["type"] = OrganType_Eyeball;
        if (RANDOM <= OrganChances[OrganType_Intestine])
			organ.nAttributes["type"] = OrganType_Intestine;
        if (RANDOM <= OrganChances[OrganType_Stomach])
			organ.nAttributes["type"] = OrganType_Stomach;
        if (RANDOM <= OrganChances[OrganType_Skin])
			organ.nAttributes["type"] = OrganType_Skin;
		if (RANDOM <= OrganChances[OrganType_Bone])
			organ.nAttributes["type"] = OrganType_Bone;

		organ.nAttributes["value"] = OrganValues[(OrganTypes)organ.nAttributes["type"]];
		organ.sAttributes["name"] = OrganNames[(OrganTypes)organ.nAttributes["type"]];

		return organ;
	}
};