#include <fstream>
#include <filesystem>

#include ".\include\SkillsClass.h"

#include ".\include\common\io_util.h"
#include ".\include\common\char_constants.h"
#include ".\include\common\string_manip.h"
#include ".\include\common\copypaste_obj.h"

#include ".\imgui.h"

void SkillsClass::write() {

	std::ofstream output;
	output.open(this->_filename, std::ios::binary);

	if (!output.is_open())
		throw new std::exception("SK_PARAM.BIN not found to be written!");

	for (size_t i = 0; i < this->_skills.size(); i++) {

		output.write((char*)this->_skills.at(i).name, 18);

		writeRaw<SkillStatsStruct>(output, this->_skills.at(i).stats);

		output.write((char*)this->_skills.at(i).description, 40);

	}

	output.close();

}

void SkillsClass::read(std::string filename) {

	this->_filename = filename;

	std::ifstream input(this->_filename, std::ios::binary);

	if (!input.is_open())
		throw new std::exception("SK_PARAM.BIN not found to be read!");

	std::filesystem::path filePath(this->_filename);
	size_t fileSize = std::filesystem::file_size(filePath);

	this->_skills.resize(fileSize / 104);		//entries are 104 bytes long

	for (size_t i = 0; i < this->_skills.size(); i++) {

		input.read(this->_skills.at(i).name, 18);

		this->_skills.at(i).stats = readRaw<SkillStatsStruct>(input);

		input.read(this->_skills.at(i).description, 40);

	}

	input.close();

}

void SkillsClass::draw() {

	ImGui::Begin("SK_PARAM");

	if (ImGui::Button("Save")) {

		this->write();

	}

	ImGui::SameLine();
	if (ImGui::Button("Copy")) {

		copyObj(&this->_skills.at(this->_skillIndex), "Skill");

	}

	ImGui::SameLine();
	if (ImGui::Button("Paste")) {

		if (checkObjType("Skill"))
			this->_skills.at(this->_skillIndex) = *((SkillStruct*)pasteObj());

	}

	if (ImGui::BeginCombo("Skill Index", this->_skills.at(this->_skillIndex).name)) {

		for (size_t i = 0; i < this->_skills.size(); i++) {

			ImGui::PushID(i);
			bool is_selected = (i == this->_skillIndex);
			if (ImGui::Selectable(this->_skills.at(i).name, is_selected))
				this->_skillIndex = i;
			if (is_selected)
				ImGui::SetItemDefaultFocus();
			ImGui::PopID();

		}

		ImGui::EndCombo();

	}

	ImGui::InputText("Name", this->_skills.at(this->_skillIndex).name, 19);
	ImGui::InputUByte("Cost Type #1", &this->_skills.at(this->_skillIndex).stats.cost1);
	ImGui::InputUByte("Cost Type #2", &this->_skills.at(this->_skillIndex).stats.cost2);
	ImGui::InputUShort("Base HP", &this->_skills.at(this->_skillIndex).stats.baseHp);
	ImGui::InputUShort("Base MP", &this->_skills.at(this->_skillIndex).stats.baseMp);
	ImGui::InputUShort("Base SP", &this->_skills.at(this->_skillIndex).stats.baseSp);
	ImGui::InputUShort("Base STR", &this->_skills.at(this->_skillIndex).stats.baseStr);
	ImGui::InputUShort("Base VIT", &this->_skills.at(this->_skillIndex).stats.baseVit);
	ImGui::InputUShort("Base ACT", &this->_skills.at(this->_skillIndex).stats.baseAct);
	ImGui::InputUShort("Base MOV", &this->_skills.at(this->_skillIndex).stats.baseMov);
	ImGui::InputUShort("Base MAG", &this->_skills.at(this->_skillIndex).stats.baseMag);
	ImGui::InputUShort("Base MEN", &this->_skills.at(this->_skillIndex).stats.baseMen);
	ImGui::InputUByte("Unknown #1", &this->_skills.at(this->_skillIndex).stats.unknown1);
	ImGui::InputUByte("Unknown #2", &this->_skills.at(this->_skillIndex).stats.unknown2);
	ImGui::InputUByte("Unknown #3", &this->_skills.at(this->_skillIndex).stats.unknown3);
	ImGui::InputUByte("Unknown #4", &this->_skills.at(this->_skillIndex).stats.unknown4);
	ImGui::InputUByte("Unknown #5", &this->_skills.at(this->_skillIndex).stats.unknown5);
	ImGui::InputByte("Increase Fire %", &this->_skills.at(this->_skillIndex).stats.increaseFirePercent);
	ImGui::InputByte("Increase Wind %", &this->_skills.at(this->_skillIndex).stats.increaseWindPercent);
	ImGui::InputByte("Increase Earth %", &this->_skills.at(this->_skillIndex).stats.increaseEarthPercent);
	ImGui::InputByte("Increase Lightning %", &this->_skills.at(this->_skillIndex).stats.increaseLightningPercent);
	ImGui::InputByte("Increase Blizzard %", &this->_skills.at(this->_skillIndex).stats.increaseBlizzardPercent);
	ImGui::InputByte("Increase Water %", &this->_skills.at(this->_skillIndex).stats.increaseWaterPercent);
	ImGui::InputByte("Increase Explosion %", &this->_skills.at(this->_skillIndex).stats.increaseExplosionPercent);
	ImGui::InputByte("Increase Forest %", &this->_skills.at(this->_skillIndex).stats.increaseForestPercent);
	ImGui::InputUByte("Special", &this->_skills.at(this->_skillIndex).stats.special);
	ImGui::InputUShort("Coin Cost Lv1", &this->_skills.at(this->_skillIndex).stats.coinCost1);
	ImGui::InputUShort("Coin Cost Lv2", &this->_skills.at(this->_skillIndex).stats.coinCost2);
	ImGui::InputUShort("Coin Cost Lv3", &this->_skills.at(this->_skillIndex).stats.coinCost3);
	ImGui::InputUShort("Coin Cost Lv4", &this->_skills.at(this->_skillIndex).stats.coinCost4);
	ImGui::InputUShort("Coin Cost Lv5", &this->_skills.at(this->_skillIndex).stats.coinCost5);
	ImGui::InputUShort("Multiplier", &this->_skills.at(this->_skillIndex).stats.multiplier);
	ImGui::InputText("Description", this->_skills.at(this->_skillIndex).description, 41);

	ImGui::End();

}

void SkillsClass::outputToCSV() {

	std::ofstream output;
	output.open(".\\csv\\SK_PARAM.CSV");

	if (!output.is_open())
		return;

	output << "name,cost type,cost type,base HP inc,base MP inc,base SP inc,base STR inc,base VIT inc,base ACT inc,base MOV inc,base MAG inc,base MEN inc,???,???,???,???,???,"
		<< "fire pow inc %,wind pow inc %,earth pow inc %,blizzard pow inc %,water pow inc %,explosion pow inc %,forest pow inc %,special,cost Lv1,cost Lv2,cost Lv3,cost Lv4,cost Lv5,multiplier,description\n";

	for (const auto& val : this->_skills) {

		output << val.name << ','
			<< std::to_string(val.stats.cost1) << ','
			<< std::to_string(val.stats.cost2) << ','
			<< std::to_string(val.stats.baseHp) << ','
			<< std::to_string(val.stats.baseMp) << ','
			<< std::to_string(val.stats.baseSp) << ','
			<< std::to_string(val.stats.baseStr) << ','
			<< std::to_string(val.stats.baseVit) << ','
			<< std::to_string(val.stats.baseAct) << ','
			<< std::to_string(val.stats.baseMov) << ','
			<< std::to_string(val.stats.baseMag) << ','
			<< std::to_string(val.stats.baseMen) << ','
			<< std::to_string(val.stats.unknown1) << ','
			<< std::to_string(val.stats.unknown2) << ','
			<< std::to_string(val.stats.unknown3) << ','
			<< std::to_string(val.stats.unknown4) << ','
			<< std::to_string(val.stats.unknown5) << ','
			<< std::to_string(val.stats.increaseFirePercent) << ','
			<< std::to_string(val.stats.increaseWindPercent) << ','
			<< std::to_string(val.stats.increaseEarthPercent) << ','
			<< std::to_string(val.stats.increaseBlizzardPercent) << ','
			<< std::to_string(val.stats.increaseWaterPercent) << ','
			<< std::to_string(val.stats.increaseExplosionPercent) << ','
			<< std::to_string(val.stats.increaseForestPercent) << ','
			<< std::to_string(val.stats.special) << ','
			<< std::to_string(val.stats.coinCost1) << ','
			<< std::to_string(val.stats.coinCost2) << ','
			<< std::to_string(val.stats.coinCost3) << ','
			<< std::to_string(val.stats.coinCost4) << ','
			<< std::to_string(val.stats.coinCost5) << ','
			<< std::to_string(val.stats.multiplier) << ','
			<< val.description << '\n';

	}

	output.close();

}