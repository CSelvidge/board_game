#include "cards.h"

/*
---------- Creation of cards via structs ----------
           Create sets of cards for each destination zone, and gandalf cards 
           Do not forget boromir         
*/

/*I didnt want to hardcode all of this, anyway encounter card state initialization loop*/
void init_encounter_states(EncounterCardState encounter_card_states[ENCOUNTER_LEN]) {
    for (int8_t i = 0; i < 42; i++) {
        encounter_card_states[i].flags = 0;
        encounter_card_states[i].owned_by = 255;
    }
}

void shuffle_cards(uint8_t cards[], size_t card_amount) { //Got this from the internet, the Fisher-Yates shuffle.
    for (int i = card_amount - 1; i > 0; i--) {       //I dont understand how this eliminates bias, but i have been told it does, and the internet never lies.
        int j = rand() % (i + 1);                   //Original suffle apparently "Overshuffles" and "N shuffles was not divisible by array indexes", look into this later.
        uint8_t temp = cards[i];
        cards[i] = cards[j];
        cards[j] = temp;
    }
}
/*Simulates drawing a card by assigning the next available card to active*/
int8_t draw_gandalf_card(uint8_t gandalf_cards[]) {
    for (int8_t i = 0; i < GANDALF_LEN; i++) {
        if (gandalf_card_states[gandalf_cards[i]].discarded || gandalf_card_states[gandalf_cards[i]].in_play) continue;
        gandalf_card_states[gandalf_cards[i]].in_play = 1;
        return 1; //If we never get to 1, every card was either discarded or is already in play (in the players hand), so we cannot draw a new card.
    }
    return 0;
}

/*Gandalf cards*/
const GandalfCardDef gandalf_card_defs[GANDALF_LEN] = { //.rodata
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

uint8_t zone_cards[7] = {0}; //7 indexes into the all_encounter_defs(cards.c) to define cards in the zone
GandalfCardState gandalf_card_states[GANDALF_LEN] = {0};

/*Boromir specific card initialization*/
const EncounterCardDef boromir = {
    .name = "Boromir",
    .text = "After losing a battle against uruk-hai: Re-roll the battle die. You lose if you roll the Sauron symbol.",
};

const EncounterCardVars boromir_vars = {
    .alignment = 1,
    .special_effect = 0,
    .combats = 0,
    .effect_variance = 0,
    .discardable = 0,
};

EncounterCardState boromir_state = {
    .flags = 1,
    .owned_by = 255 //255 is a placeholder for a card not owned by a player, think of it as owned by the "board"
};

/*I hate this, is there not a better way of doing this? Anyway this is the encounter card initialization*/
const EncounterCardDef encounter_card_defs[ENCOUNTER_LEN] = {
    { //Lothlorien
        .name = "Cave Troll",
        .text = "There is something large waiting in the tunnels.",
    },
    {
        .name = "Saruman",
        .text = "Place two Uruk-hai in Isenguard. If there are fewer than two  Uruk-hai in the supply, place as many as possible in Isenguard."
    },
    {
        .name = "Nazgul",
        .text = "Place one nazgul in Minas Morgul. If, after placement, all of the Nazgul are in Minas Morgul, you immediately lose."
    },
    {
        .name = "Balrog of Moria",
        .text = "Place the Gandalf token in Helm's Deep. You may no longer use Gandalf cards until the Ring-Bearer has reached Helm's Deep."
    },
    {
        .name = "Moria Orc",
        .text = "Small, nimble, and nard to handle."
    },
    {
        .name = "Arwen",
        .text = "Ignore the event associated with one gameboard space."
    },
    {
        .name = "Elrond",
        .text = "Immediately after a roll: Re-roll one die of your choice. Only the new value counts."
    },
    {//Rohan
        .name = "Orc Hordes",
        .text = "An overwhelming force!"
    },
    {
        .name = "Wargs",
        .text = "A nasty surprise with teeth and claws"
    },
    {
        .name = "King Theoden",
        .text = "Advance one Fellowship figure, other than the Ring-bearer, to their current stage's destination space."
    },
    {
        .name = "Nazgul",
        .text = "Place one nazgul in Minas Morgul. If, after placement, all of the Nazgul are in Minas Morgul, you immediately lose."
    },
    {
        .name = "Uruk-hai",
        .text = "For each Uruk-hai in Isenguard: Battle for one courage. If you win at least one of the battles, remove one Uruk-hai (not the cheiftan)."
    },
    {
        .name = "Saruman",
        .text = "Place two Uruk-hai in Isenguard. If there are fewer than two  Uruk-hai in the supply, place as many as possible in Isenguard."
    },
    {
        .name = "Galadriel",
        .text = "Before rolling in a battle: Move the One Ring to the Galadriel space on the courage track."
    },
    {//Helm's Deep
        .name = "Eowyn",
        .text = "If you roll a 6 during your encounter with Witch-King of Angmarm immediately remove all Nazgul, the Witch-King and his encounter card from the game."
    },
    {
        .name = "Wormtongue",
        .text = "Choose one of your friend cards and remove it from the game without using it."
    },
    {
        .name = "Eomer and the Riders of Rohan",
        .text = "Instead of rolling in a battle: Without having to roll, automatically win one battle."
    },
    {
        .name = "Nazgul",
        .text = "Place one nazgul in Minas Morgul. If, after placement, all of the Nazgul are in Minas Morgul, you immediately lose."
    },
    {
        .name = "Uruk-hai",
        .text = "For each Uruk-hai in Isenguard: Battle for one courage. If you win at least one of the battles, remove one Uruk-hai (not the cheiftan)."
    },
    {
        .name = "Orc Hordes",
        .text = "An overwhelming force!"
    },
    {
        .name = "Saruman",
        .text = "Place two Uruk-hai in Isenguard. If there are fewer than two  Uruk-hai in the supply, place as many as possible in Isenguard."
    },
    {//Gondor
        .name = "Nazgul",
        .text = "Place one Nazgul in Minas Morgul. If, after placement, all of the Nazgul are in Minas Morgul, you immediately lose."
    },
    {
        .name = "Grond",
        .text = "The battering ram destroys wood and stone, gate and wall."
    },
    {
        .name = "Orc Hordes",
        .text = "An overwhelming force!"
    },
    {
        .name = "Sauron's Eye",
        .text = "On the courage track, move the One Ring to the space with Sauron's eye. If it is already on or past this space, nothing happens."
    },
    {
        .name = "Uruk-hai",
        .text = "For each Uruk-hai in Isenguard: Battle for one courage. If you win at least one of the battles, remove one Uruk-hai (not the cheiftan). Has isenguard already been freed of all Uruk-hai? If so gain a courage."
    },
    {
        .name = "Faramir",
        .text = "Before your turn: Advance the ring-bearer two to four spaces."
    },
    {
        .name = "Treebeard",
        .text = "Either: Gain two courage, or place the Treebeard token in Isenguard. From now on after every battle won in Isenguard, remove one Uruk-hai, and, ultimately, remove the cheiftan."
    },
    {//Minas Morgul
        .name = "Witch-King of Angmar",
        .text = "For each Nazgul in Minas Morgul, roll one black encounter die (including for the Witch-King himself). For each odd number lose a courage."
    },
    {
        .name = "Momakil",
        .text = "The grey giants rage in battle."
    },
    {
        .name = "Haradrim",
        .text = "The enemy has allies too."
    },
    {
        .name = "Denethor",
        .text = "You must re-roll one of the multicolored Fellowship die that is places on the dice board"
    },
    {
        .name = "Army of the Dead",
        .text = "Place this card on top of a card to the left or right of it. That card remains invalid until the Army of the Dead moves on."
    },
    {
        .name = "Uruk-hai",
        .text = "For each Uruk-hai in Isenguard: Battle for one courage. If you win at least one of the battles, remove one Uruk-hai (not the cheiftan). Has isenguard already been freed of all Uruk-hai? If so gain a courage."
    },
    {
        .name = "Sauron's Mouth",
        .text = "Keep fighting battles until you have won two in a row. Each combat is one courage."
    },
    {//Mount Doom
        .name = "Gollum's Deciet",
        .text = "A bitter fightn over the ring"
    },
    {
        .name = "Phial of Galadriel",
        .text = "A shining ray of courage"
    },
    {
        .name = "Gollum's Madness",
        .text = "Greed paralyzes the mind"
    },
    {
        .name = "Shelob",
        .text = "Caught in the web of a giant spider, lose one courage, the ring bearer does not move during this turn"
    },
    {
        .name = "Shelob's Sting",
        .text = "Roll one black encounter die: 1: You're in luck! 2-3: Lose one courage. 4-6:Lose two courage."
    },
    {
        .name = "TheOne Ring's Power",
        .text = "1-5: You're in luck! 6: Lose 5 courage"
    },
    {
        .name = "Eagles",
        .text = "A small sign of hope"
    }
};

const EncounterCardVars encounter_card_vars[ENCOUNTER_LEN] = {
    {
        .alignment = 0,
        .special_effect = 1,
        .combats = 1,
        .effect_variance = -2,
        .discardable = 0
    },
    {
        .alignment = 0,
        .special_effect = 3,
        .combats = 0,
        .effect_variance = 2,
        .discardable = 0
    },
    {
        .alignment = 0,
        .special_effect = 4,
        .combats = 0,
        .effect_variance = 1,
        .discardable = 0
    },
    {
        .alignment = 0,
        .special_effect = 2,
        .combats = 0,
        .effect_variance = -3,
        .discardable = 1
    },
    {
        .alignment = 0,
        .special_effect = 1,
        .combats = 1,
        .effect_variance = -1,
        .discardable = 0
    },
    {
        .alignment = 1,
        .special_effect = 0,
        .combats = 0,
        .effect_variance = 0,
        .discardable = 0,
    },
    {
        .alignment = 1,
        .special_effect = 0,
        .combats = 0,
        .effect_variance = 0,
        .discardable = 0,
    },
    {
        .alignment = 0,
        .special_effect = 1,
        .combats = 1,
        .effect_variance = -2,
        .discardable = 0
    },
    {
        .alignment = 0,
        .special_effect = 2,
        .combats = 0,
        .effect_variance = -2,
        .discardable = 1
    },
    {
        .alignment = 1,
        .special_effect = 0,
        .combats = 0,
        .effect_variance = 0,
        .discardable = 0
    },
    {
        .alignment = 0,
        .special_effect = 4,
        .combats = 0,
        .effect_variance = 1,
        .discardable = 0
    },
    {
        .alignment = 0,
        .special_effect = 1,
        .combats = 6, //6  is a special value that means "Check boardstate for how many battles"
        .effect_variance = -1,
        .discardable = 0
    },
    {
        .alignment = 0,
        .special_effect = 3,
        .combats = 0,
        .effect_variance = 2,
        .discardable = 0
    },
    {
        .alignment = 1,
        .special_effect = 2,
        .combats = 0,
        .effect_variance = 0,
        .discardable = 0
    },
    {
        .alignment = 1,
        .special_effect = 1,
        .combats = 0,
        .effect_variance = 0,
        .discardable = 0
    },
    {
        .alignment = 0,
        .special_effect = 0,
        .combats = 0,
        .effect_variance = 0,
        .discardable = 0
    },
    {
        .alignment = 1,
        .special_effect = 0,
        .combats = 0,
        .effect_variance = 0,
        .discardable = 0
    },
    {
        .alignment = 0,
        .special_effect = 4,
        .combats = 0,
        .effect_variance = 1,
        .discardable = 0
    },
    {
        .alignment = 0,
        .special_effect = 1,
        .combats = 6,
        .effect_variance = -1,
        .discardable = 0
    },
    {
        .alignment = 0,
        .special_effect = 1,
        .combats = 1,
        .effect_variance = -2,
        .discardable = 0
    },
    {
        .alignment = 0,
        .special_effect = 3,
        .combats = 0,
        .effect_variance = 2,
        .discardable = 0
    },
    {
        .alignment = 0,
        .special_effect = 4,
        .combats = 0,
        .effect_variance = 1,
        .discardable = 0
    },
    {
        .alignment = 0,
        .special_effect = 2,
        .combats = 0,
        .effect_variance = -3,
        .discardable = 1
    },
    {
        .alignment = 0,
        .special_effect = 1,
        .combats = 1,
        .effect_variance = -2,
        .discardable = 0
    },
    {
        .alignment = 0,
        .special_effect = 2,
        .combats = 0,
        .effect_variance = 255, //Special value that will correspond to a rule in the game loop
        .discardable = 1
    },
    {
        .alignment = 0,
        .special_effect = 1,
        .combats = 7, //Special value that has to correspond to number of combats, and check if isenguard has been cleared by treebeard
        .effect_variance = -1,
        .discardable = 0
    },
    {
        .alignment = 1, //Faramir
        .special_effect = 0,
        .combats = 1,
        .effect_variance = 0,
        .discardable = 0
    },
    {
        .alignment = 1, //Treebeard
        .special_effect = 0,
        .combats = 0,
        .effect_variance = 0,
        .discardable = 0
    },
    {
        .alignment = 0,
        .special_effect = 2,
        .combats = 8, //Special value for the Witch-Kking of Angmar combat
        .effect_variance = -1,
        .discardable = 0
    },
    {
        .alignment = 0,
        .special_effect = 1,
        .combats = 2,
        .effect_variance = -2,
        .discardable = 0
    },
    {
        .alignment = 0,
        .special_effect = 2,
        .combats = 0,
        .effect_variance = -2,
        .discardable = 0
    },
    {
        .alignment = 0,
        .special_effect = 0,
        .combats = 0,
        .effect_variance = 0,
        .discardable = 0
    },
    {
        .alignment = 0,
        .special_effect = 0,
        .combats = 0,
        .effect_variance = 0,
        .discardable = 0
    },
    {
        .alignment = 0,
        .special_effect = 1,
        .combats = 7, //Special value that has to correspond to number of combats, and check if isenguard has been cleared by treebeard
        .effect_variance = -1,
        .discardable = 0
    },
    {
        .alignment = 0,
        .special_effect = 1,
        .combats = 9, //Sauron's mouth special combat effect
        .effect_variance = 1,
        .discardable = 1
    },
    {
        .alignment = 3,
        .special_effect = 2,
        .combats = 0,
        .effect_variance = -2,
        .discardable = 0
    },
    {
        .alignment = 3,
        .special_effect = 2,
        .combats = 0,
        .effect_variance = 2,
        .discardable = 0
    },
    {
        .alignment = 3,
        .special_effect = 2,
        .combats = 0,
        .effect_variance = -1,
        .discardable = 0
    },
    {
        .alignment = 3,
        .special_effect = 2,
        .combats = 0,
        .effect_variance = -1,
        .discardable = 0
    },
    {
        .alignment = 3,
        .special_effect = 2,
        .combats = 0,
        .effect_variance = -3, //Special value that will correspond to Shelob's sting special game rule
        .discardable = 0
    },
    {
        .alignment = 3,
        .special_effect = 2,
        .combats = 0,
        .effect_variance = -5, //Special value that will correspond to The One Ring's Power special game rule
        .discardable = 0
    },
    {
        .alignment = 3,
        .special_effect = 2,
        .combats = 0,
        .effect_variance = 1,
        .discardable = 0
    }
};

/*I hated that, a lot*/
