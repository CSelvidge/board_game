#include "cards.h"

/*
---------- Creation of cards via structs ----------
           Create sets of cards for each destination zone, and gandalf cards 
           Do not forget boromir         
*/


void init_boromir(EncounterCardDef* boromir, EncounterCardState* boromir_state) {
    boromir->name = "Boromir";
    boromir->text = "After losing a battle against uruk-hai: Re-roll the battle die. You lose if you roll the Sauron symbol.",
    boromir->alignment = 1;
    boromir->special_effect = 0;
    boromir->effect_variance = 0;

    boromir_state->flags = 0;
    boromir_state->owned_by = 0;
}

void init_gandalf_cards(GandalfCardDef card_defs[], GandalfCardState card_states[]) {

    for (uint8_t i = 0; i < 5; i++) {
        card_states[i].discarded = 0;
    }

    card_defs[0] = (GandalfCardDef) {
        .title = "Gandalf's Power",
        .text = "After a roll: Turn one black encounter die to any face.",
    };
    card_defs[1] = (GandalfCardDef) {
        .title = "Gandalf's Trick",
        .text = "After a roll: Turn one multicored Fellowship die of your choice to any face",
    };
    card_defs[2] = (GandalfCardDef) {
        .title = "Gandalf's Support",
        .text = "Before a turn: Roll all the multicolored Fellowship dice. Choose one die and move the corresponding figure accordingly.",
    };
    card_defs[3] = (GandalfCardDef) {
        .title = "Gandalf's Vision",
        .text = "Look at the top card of the next encounter stack. Then either put it back or remove it from the game.",
    };
    card_defs[4] = (GandalfCardDef) {
        .title = "Gandalf's Wrath",
        .text = "Remove one encounter card from the game as soon as you have activated it and performed its instructions.",
    };
}

