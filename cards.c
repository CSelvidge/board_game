#include "cards.h"

/*
---------- Creation of cards via structs ----------
           Create sets of cards for each destination zone, and gandalf cards 
           Do not forget boromir         
*/

const GandalfCardDef gandalf_card_defs[5] = {
    {
        .title = "Gandalf's Power",
        .text = "After a roll: Turn one black encounter die to any face.",
    },
    {
        .title = "Gandalf's Trick",
        .text = "After a roll: Turn one multicored Fellowship die of your choice to any face",
    },
    {
        .title = "Gandalf's Support",
        .text = "Before a turn: Roll all the multicolored Fellowship dice. Choose one die and move the corresponding figure accordingly.",
    },
    {
        .title = "Gandalf's Vision",
        .text = "Look at the top card of the next encounter stack. Then either put it back or remove it from the game.",
    },
    {
        .title = "Gandalf's Wrath",
        .text = "Remove one encounter card from the game as soon as you have activated it and performed its instructions.",
    }
};

const GandalfCardState gandalf_card_states[5] = {
    {0},{0},{0},{0},{0}
};

const EncounterCardDef boromir = {
    .name = "Boromir",
    .text = "After losing a battle against uruk-hai: Re-roll the battle die. You lose if you roll the Sauron symbol.",
    .alignment = 1,
    .special_effect = 0,
    .effect_variance = 0
};

const EncounterCardState boromir_State = {
    .flags = 1,
    .owned_by = 255 //255 is a placeholder for a card not owned by a player, think of it as owned by the "board"
};

const EncounterCardDef encounter_Card_Defs[42] = {

}
