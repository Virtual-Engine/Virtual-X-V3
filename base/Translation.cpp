#include "common.hpp"
#include "Translation.hpp"

std::vector<TranslationString*> TranslationString::TranslationTable;

void TranslationString::Register() {
	TranslationTable.push_back(this);
	bHasTranslation = true;
}