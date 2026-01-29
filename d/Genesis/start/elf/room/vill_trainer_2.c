#include "../stddefs.h"
#include "/sys/stdproperties.h"
#include "/sys/ss_types.h"
#include "/sys/language.h"
#include "/sys/money.h"
#include "/sys/macros.h"

#pragma save_binary

inherit "/lib/skill_raise";
inherit ELFROOM;


#define SOUTH     ROOMDIR + "vill_trainer_1"

#define NAT_SHORT "In the home of sergeant Bullwhip"
#define FOR_SHORT "In the home of the hobgoblin sergeant"

#define NAT_LONG \
  "You are in an empty stone hall. The only decoration on the roughcast "+\
  "white walls are a few well-used, well-oiled weapons and shields. " + \
  "There is no furniture, just an empty floor of wide oak planks. " + \
  "Several high, narrow window openings let in sunlight and air.\n" + \
  "The sergeant Bullwhip is here. " + \
  "He is a middle-aged, burly hobgoblin, " +\
  "looking disapprovingly at whatever his eyes fall upon.\n" + \
  "There is an instructive sign on the wall, written with bold, " + \
  "uneven block letters.\n"
#define FOR_LONG \
  "You are in an empty stone hall. The only decoration on the roughcast "+\
  "white walls are a few well-used, well-oiled weapons and shields. " + \
  "There is no furniture, just an empty floor of wide oak planks. " + \
  "Several high, narrow window openings let in sunlight and air.\n" + \
  "There is an middle-aged, burly hobgoblin here. He doesn't seem to " + \
  "be prone to smile very often, and he is " +\
  "looking disapprovingly at whatever his eyes fall upon.\n" +\
  "There is an instructive sign on the wall, written with bold, " + \
  "uneven block letters.\n"

#define INSTRUCTIONS \
  "If you are good enough, I can train you to "+\
  "swim, climb, or fight with sword or knife.\n\n" +\
  "<learn> will tell you "+\
  "what new skills you can learn, and <improve> will tell what old skills " +\
  "you can improve.\n"

#define SHIELD_ITEM ({"shield", "shields", "arms", "coat of arms"})
#define SHIELD_NDESC \
  "On each shield there is a different coat of arms, but they all belong " + \
  "to the guards of prominent elven lords. " + \
  "The shields are all chained to the walls\n"
#define SHIELD_FDESC \
  "On each shield there is a different coat of arms, and " + \
  "the shields are all chained to the walls\n"

#define FLOOR_ITEM ({"floor", "floors", "plank", "planks", "oak planks"})
#define FLOOR_DESC \
  "The floor's sturdy, wide oak planks are scuffed and scratched all over " +\
  "by heavy boots, and nicked in several places by sharp weapons.\n"

#define WEAPON_ITEM ({"weapon", "weapons"})
#define WEAPON_DESC \
  "There are several different weapons; all seem to have been used " +\
  "often, but they are tended impeccably, their edges sharp and their " + \
  "surface shining. All are, however, safely chained to the wall.\n"

#define CHAIN_ITEM ({"chain", "chains", "scroll", "scrolls"})
#define CHAIN_DESC \
  "The chains are made out of sturdy dwarven iron.\n"

#define HOBGOBLIN_ITEM ({"hobgoblin", "hobgoblin sergeant", "bullwhip", \
			 "sergeant", \
			 "sergeant bullwhip"})
#define HOBGOBLIN_DESC \
  "He is middle-aged, with burly hair and tail. He has an ugly, pushed-in " +\
  "face, similar to a bulldog's, which isn't made any lovelier by huge, " +\
  "yellowish fangs and a proliferation of scars and wrinkles. " +\
  "His ears are pointed, protuberant, and tufted with graying hair, and the "+\
  "hair on his head is more adequately described as a pelt. He is dressed " +\
  "in a simple chainmail, greenish brown tunic, and high, soft boots.\n"
#define HOBGOBLIN_NAME \
   check_call(N_KNOW("sergeant Bullwhip", "hobgoblin sergeant"))

#define SIGN_ITEM ({"sign", "plate" })
#define SIGN_DESC   "The sign reads:\n" 


#define FAIL_NO_MORE_TO_LEARN \
  "The " + HOBGOBLIN_NAME + " says: There are no more new skills I can " + \
  "teach you. Why not concentrate on improving those you have?\n"
#define FAIL_NO_MORE_TO_IMPROVE \
  "The " + HOBGOBLIN_NAME + " says: There is nothing more I can " + \
  "teach you. You have to seek more wisdom elsewhere\n"
#define FAIL_NO_SKILLS_TO_IMPROVE \
  "The " + HOBGOBLIN_NAME + " says: There is nothing more I can " + \
  "teach you. You have to seek more wisdom elsewhere\n"
#define FAIL_SKILL_UNAVAILIABLE(SKILL) \
  "The " + HOBGOBLIN_NAME + " sighs and says: Sorry, but the " + SKILL +\
  " skill is nothing I am able to teach you. \n"
#define FAIL_ALREADY_LEARNT \
  "The " + HOBGOBLIN_NAME + " looks confused and says: " + \
  "But I can see that you already " + \
  "have learned the basics of that skill. You have to improve it to learn " + \
  "more.\n"
#define FAIL_NOT_LEARNT \
  "The " + HOBGOBLIN_NAME + " looks stern and says: " + \
  "Oh no, you cannot improve a skill until you have learned the " + \
  "basics of it.\n"
#define FAIL_CANNOT_LEARN \
  "The " + HOBGOBLIN_NAME + " works diligently, but you fail to " + \
  "grasp what he teaches you.\n"
#define FAIL_CANT_RISE_MORE \
  "The " + HOBGOBLIN_NAME + " says: " + \
  "I am sorry, but there is nothing more I can teach you on that subject. " + \
  "You have to find a better teacher than I.\n"
#define FAIL_COST(COST) \
  "You cannot find the " + COST + " coppers you need to pay the " + \
  HOBGOBLIN_NAME + ".\n"

create_room()
{
    set_short(N_KNOW(NAT_SHORT, FOR_SHORT));
    set_long( N_KNOW(WRAP(NAT_LONG),
	WRAP(FOR_LONG)));

    add_item(   SHIELD_ITEM, WRAP(N_KNOW(SHIELD_NDESC, SHIELD_FDESC)));
    add_item(    FLOOR_ITEM, WRAP(    FLOOR_DESC));
    add_item(    CHAIN_ITEM, WRAP(    CHAIN_DESC));
    add_item(   WEAPON_ITEM, WRAP(   WEAPON_DESC));
    add_item(HOBGOBLIN_ITEM, WRAP(HOBGOBLIN_DESC));
    add_item(     SIGN_ITEM, WRAP(     SIGN_DESC + INSTRUCTIONS)); 

    add_cmd_item(SIGN_ITEM, "read", WRAP(SIGN_DESC + INSTRUCTIONS));

    add_prop(ROOM_I_INSIDE, 1);

    add_exit(SOUTH,      "south", 0);

    stock();
    create_skill_raise();
    set_up_skills();
}


stock()
{
}

init() 
{
    init_skill_raise();
    ::init();
}


set_up_skills() {
    sk_add_train(SS_WEP_SWORD,"fight with a sword","sword",100,30);
    sk_add_train(SS_WEP_KNIFE,"fight with a knife","knife",100,30);
    sk_add_train(SS_DEFENCE,"fight defensively","defence",100,20);
    sk_add_train(SS_UNARM_COMBAT,"fight without weapons",
      "unarmed combat",100,30);
    sk_add_train(SS_TRACKING,"tracking","tracking",100,30);
    sk_add_train(SS_HUNTING,"hunting","hunting",100,30);
    sk_add_train(SS_SWIM,"swimming","swimming",100,30);
    sk_add_train(SS_CLIMB,"climbing","climbing",100,30);
    sk_add_train(SS_TRADING,"trading","trading",100,30);
    sk_add_train(SS_HERBALISM,"herbalism","herbalism",100,20);
    sk_add_train(SS_SPELLCRAFT,"spellcraft","spellcraft",100,20);
    sk_add_train(SS_AWARENESS,"awareness","awareness",100,30);
    sk_add_train(SS_ANI_HANDL,"animal handling","animal handling",100,20);
    sk_add_train(SS_LOC_SENSE,"location sense","location sense",100,30);
    sk_add_train(SS_FR_TRAP,"find and remove traps","find and remove traps",100,20);
}


/*
 * Below are functions that modify the standard skill_raise behaviour. 
 */

int sk_hook_unknown_skill(string skill, string verb)
{
    notify_fail(WRAP(FAIL_SKILL_UNAVAILIABLE(skill)));
    return 0;
}

void sk_hook_raise_rank(int snum, int to_lev, int cost)
{
    string rank, long_str;

    rank = sk_rank(to_lev);

    this_player()->catch_msg(WRAP("The "+ HOBGOBLIN_NAME +
	" helps you raise your " +
	sk_tdesc[snum][0] + " skill.\n"));
    write(WRAP("Thanks to this, you now may call yourself " +
	rank + " in this skill.\n"));

    say(WRAP(QCTNAME(this_player()) + " is taught the " +
	sk_tdesc[snum][1] + " skill, recieving the rank of " + 
	rank + ".\n"));
}

int sk_hook_improve_unknown(string skill)
{
    notify_fail(WRAP(FAIL_NOT_LEARNT));
    return 0;
}

int sk_hook_learn_known(string skill)
{
    notify_fail(WRAP(FAIL_ALREADY_LEARNT));
    return 0;
}

int sk_hook_cant_train(string skill, int to_lev)
{
    notify_fail(WRAP(FAIL_CANT_RISE_MORE));
    return 0;
}

int sk_hook_cant_pay(string skill, int to_lev, int cost)
{
    notify_fail(WRAP(FAIL_COST(cost)));
    return 0;
}

int sk_hook_no_list_learn()
{
    write(WRAP(FAIL_NO_MORE_TO_LEARN));
    return 1;
}

int sk_hook_no_list_improve()
{
    write(WRAP(FAIL_NO_MORE_TO_IMPROVE));
    return 1;
}

int sk_hook_improved_max(string skill)
{
    notify_fail(WRAP(FAIL_CANT_RISE_MORE));
    return 0;
}
