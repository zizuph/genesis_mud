#include "../stddefs.h"
#include "/sys/stdproperties.h"
#include "/sys/ss_types.h"
#include "/sys/language.h"
#include "/sys/money.h"
#include "/sys/macros.h"

#pragma save_binary

inherit "/lib/skill_raise";
inherit ELFROOM;


#define SOUTH     ROOMDIR + "vill_scholar_1"

#define NAT_SHORT "In the home of the widow Wormwood"
#define FOR_SHORT "In the home of the centauress scholar"

#define NAT_LONG \
  "You are in a spacious, spartan, almost barren room. " + \
  "To be certain, " + \
  "the walls are covered with shelves wherever there isn't a window or " + \
  "door, but the only other furniture are a few soft carpets and "+\
  "pillows on the floor. The shelves are filled with books and scrolls, "+\
  "locked in behind iron bars, and the windows are large and partly open, " +\
  "letting in sunlight and air.\n" + \
  "The widow Wormwood is here. She is an elderly, white-maned centauress, " +\
  "moving with the stiffness of age and gout, but she still has the " + \
  "twinkle of humour and intelligence in her sharp-sighted eyes.\n " + \
  "There is an instructive sign on the wall, written in a curly, " + \
  "determined longhand.\n"
#define FOR_LONG \
  "You are in a spacious, spartan, almost barren room. The only " + \
  "furniture is book-shelves around the walls, and a few soft carpets and "+\
  "pillows on the floor.\n" + \
  "There is an elderly, white-maned centauress here. She is moving " +\
  "with the stiffness of age and gout, but she still has the twinkle " + \
  "of humour and intelligence in her sharp-sighted eyes.\n " + \
  "There is an instructive sign on the wall, written in a curly, " + \
  " determined longhand.\n"

#define INSTRUCTIONS \
  "Welcome to my room of knowledge. I am fully qualified to "+\
  "teach you " + \
  "general spellcraft, location sense, tracking, hunting, some linguistics, "+\
  "and how to pay attention to your surroundings.\n\n<learn> will tell you "+\
  "what new skills you can learn, and <improve> will tell what old skills " +\
  "you can improve.\n"



#define SHELF_ITEM ({"shelf", "book-shelf", "shelves", "book-shelves"})
#define SHELF_DESC \
  "The shelves are filled with books, neatly arranged after subject and "+\
  "author, and with tidily labeled scrolls. Sturdy iron bars prohibit "+\
  "any browsing.\n"

#define CARPET_ITEM ({"carpet", "carpets", "pillow", "pillows", "floor"})
#define CARPET_DESC \
  "On the floor's sturdy, wide oak planks soft pillows and carpets in " +\
  "neutral colours are arranged for relaxation and restfull studying.\n"

#define BOOK_ITEM ({"book", "books", "scroll", "scrolls"})
#define BOOK_DESC \
  "The books and scrolls seem to be " +\
  "written for scholastic people by scholastic people, " +\
  "dealing with strange and esoteric subjects.\n"

#define BAR_ITEM ({"bar", "bars"})
#define BAR_DESC \
  "The bars are made out of sturdy dwarven iron.\n"

#define CENTAURESS_ITEM ({"centauress", "centaur", "wormwood", "widow", \
			  "widow wormwood"})
#define CENTAURESS_DESC \
  "She is elderly, with white hair and tail. Her eyes are pale blue and " + \
  "sharp-sighted, looking out from a tanned, sun-creased face with " +\
   "humour and intelligence. She is dressed in a slightly old-fashioned " +\
  "blouse and bodice, tied around her waist with a brightly patterned "+\
  "kerchief, as her lower body is unclad in the traditional centaur fashion.\n"
#define CENTAURESS_NAME \
   check_call(N_KNOW("widow Wormwood", "centauress scholar"))

#define SIGN_ITEM ({"sign", "plate" })
#define SIGN_DESC   "The sign reads:\n" 


#define FAIL_NO_MORE_TO_LEARN \
  "The " + CENTAURESS_NAME + " says: There are no more new skills I can " + \
  "teach you. Why not concentrate on improving those you have?\n"
#define FAIL_NO_MORE_TO_IMPROVE \
  "The " + CENTAURESS_NAME + " says: There is nothing more I can " + \
  "teach you. You have to seek more wisdom elsewhere\n"
#define FAIL_NO_SKILLS_TO_IMPROVE \
  "The " + CENTAURESS_NAME + " says: There is nothing more I can " + \
  "teach you. You have to seek more wisdom elsewhere\n"
#define FAIL_SKILL_UNAVAILIABLE(SKILL) \
  "The " + CENTAURESS_NAME + " sighs and says: Sorry, but the " + SKILL +\
  " skill is nothing I am able to teach you. \n"
#define FAIL_ALREADY_LEARNT \
  "The " + CENTAURESS_NAME + " looks confused and says: " + \
  "But I can see that you already " + \
  "have learned the basics of that skill. You have to improve it to learn " + \
  "more.\n"
#define FAIL_NOT_LEARNT \
  "The " + CENTAURESS_NAME + " looks stern and says: " + \
  "Oh no, you cannot improve a skill until you have learned the " + \
  "basics of it.\n"
#define FAIL_CANNOT_LEARN \
  "The " + CENTAURESS_NAME + " works diligently, but you fail to " + \
  "grasp what she teaches you.\n"
#define FAIL_CANT_RISE_MORE \
  "The " + CENTAURESS_NAME + " says: " + \
  "I am sorry, but there is nothing more I can teach you on that subject. " + \
  "You have to find a better teacher than I.\n"
#define FAIL_COST(COST) \
  "You cannot find the " + COST + " coppers you need to pay the " + \
  CENTAURESS_NAME + ".\n"

create_room()
{
    set_short(N_KNOW(NAT_SHORT, FOR_SHORT));
    set_long( N_KNOW(WRAP(NAT_LONG),
	WRAP(FOR_LONG)));

    add_item(     SHELF_ITEM, WRAP(     SHELF_DESC));
    add_item(    CARPET_ITEM, WRAP(    CARPET_DESC));
    add_item(       BAR_ITEM, WRAP(       BAR_DESC));
    add_item(      BOOK_ITEM, WRAP(      BOOK_DESC));
    add_item(CENTAURESS_ITEM, WRAP(CENTAURESS_DESC));
    add_item(      SIGN_ITEM, WRAP(      SIGN_DESC + INSTRUCTIONS)); 

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


set_up_skills() 
{
    sk_add_train(SS_SPELLCRAFT, "spellcraft", "spellcraft", 100, 20);
    sk_add_train(SS_ELEMENT_LIFE, "life spells", "life spells",
      100, 20);
    sk_add_train(SS_HERBALISM, "find and identify herbs",
      "herbalism", 100, 10);
    sk_add_train(SS_ALCHEMY, "alchemy","alchemy", 100, 10);
    sk_add_train(SS_ELEMENT_EARTH, "earth spells",
      "earth spells", 100, 15);
    sk_add_train(SS_LANGUAGE, "language", "language", 100, 30);
    sk_add_train(SS_AWARENESS, "awareness", "awareness", 100, 30);
    sk_add_train(SS_LOC_SENSE, "location sense", "location sense", 100, 30);
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

    this_player()->catch_msg(WRAP("The " + CENTAURESS_NAME +
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
    notify_fail(WRAP(FAIL_CANNOT_LEARN));
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
