#include "cards.h"

/*
---------- Creation of cards via structs ----------
           Create sets of cards for each destination zone, and gandalf cards 
           Do not forget boromir         
*/


EncounterCardDef init_boromir_def(EncounterCardDef boromir) {
    boromir = (EncounterCardDef) {
        .name = "Boromir",
        .text = "After losing a battle against uruk-hai: Re-roll the battle die. You lose if you roll the Sauron symbol.",
        .alignment = 1,
        .special_effect = 0,
        .effect_variance = 0
    };

    return boromir;
}

void init_gandalf_cards(GandalfCardDef card_defs[], GandalfCardState card_states[]) {
    cards[0] = (GandalfCardDef) {
        .title = "Gandalf's Power",
        .text = "After a roll: Turn one black encounter die to any face.",
    };
    cards[1] = (GandalfCardDef) {
        .title = "Gandalf's Trick",
        .text = "After a roll: Turn one multicored Fellowship die of your choice to any face",
    };
    cards[2] = (GandalfCardDef) {
        .title = "Gandalf's Support",
        .text = "Before a turn: Roll all the multicolored Fellowship dice. Choose one die and move the corresponding figure accordingly.",
    };
    cards[3] = (GandalfCardDef) {
        .title = "Gandalf's Vision",
        .text = "Look at the top card of the next encounter stack. Then either put it back or remove it from the game.",
    };
    cards[4] = (GandalfCardDef) {
        .title = "Gandalf's Wrath",
        .text = "Remove one encounter card from the game as soon as you have activated it and performed its instructions.",
    };
}

