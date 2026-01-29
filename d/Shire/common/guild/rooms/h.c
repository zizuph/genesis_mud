/*
 *   /d/Shire/common/guild/hguild.c
 *   The guildroom of the Hin Warrior Guild.
 */
inherit "/lib/guild_support"; 
inherit "/lib/skill_raise";
inherit "std/room";

#include "defs.h"
#include "/sys/ss_types.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/sys/language.h"
#include "/sys/money.h"

#define STATUETTE	HIN_DIR + "statue"
#define NUM		sizeof(query_money_types())
#define CLOSED		0	/* 1 = closed,   0 = open.  */

/* Skills that are affected by our guild stat */
#define GUILD_STAT_SKILLS ({ \
		SS_FORM_TRANSMUTATION,	SS_FORM_ILLUSION, \
		SS_FORM_DIVINATION,	SS_FORM_ENCHANTMENT, \
		SS_FORM_CONJURATION,	SS_FORM_ABJURATION, \
		SS_ELEMENT_FIRE,	SS_ELEMENT_AIR, \
		SS_ELEMENT_EARTH,	SS_ELEMENT_WATER, \
		SS_ELEMENT_LIFE,	SS_ELEMENT_DEATH })

int closed;
object meditate, board;
string name;

/* Prototypes */
void reset_room();
void set_up_skills();

void
create_room()
{
   if (!present("board",this_object()))
   {
      board = clone_object("/std/board");
      name = HIN_DIR + "boards";
      if (file_size(name) != -2)
         mkdir(name);

      board->set_board_name(name + "/guildboard");
      board->set_num_notes(30);
      board->set_silent(1);
      board->set_show_lvl(0);
      board->set_remove_lvl(0);
      board->set_remove_str("You burn your fingers trying to remove a note");
      board->move(this_object());
   }

   clone_object(HIN_DIR + "ranker")->move(this_object());

   set_short("Hin Training Room");
   set_long(break_string(
     "You are standing inside a huge training room, where the Hin Warriors "
   + "learn or improve their skills. They also come here to make suggestions "
   + "on the board, or exchange knowledge about the world. Some even "
   + "meditate here, to find a new internal balance. "
   + "To the east is an opening with a forcefield in front of it. High "
   + "Hin Warriors are rumored to be able to go through it. "
   + "To the north is another protected opening, leading the the meeting "
   + "room of the guild's Council. A sign hangs on the wall. "
   + "Remember to adore the Great Nob Nar!\n",70));

   add_item("sign", "The sign has some instructions written on it.\n");
   add_item("forcefield", "A soft blue aura surrounds the opening.\n");

   add_exit(HINROOM_DIR + "partydisp", "east", "@@try_east");
   add_exit(HINROOM_DIR + "council", "north", "@@try_north");
   add_exit(HINROOM_DIR + "hall1", "west",0,0);

   add_prop(ROOM_I_NO_ATTACK, 1);
   add_prop(ROOM_I_NO_STEAL, 1);
   add_prop(ROOM_I_NO_MAGIC_ATTACK, 1);
   add_prop(ROOM_I_INSIDE,1);

   create_skill_raise();
   create_guild_support();
   set_up_skills();
   reset_room();
}

void
init()
{
   int old_stat, new_stat;
   object tp;

   ::init();

   init_guild_support();
   init_skill_raise();

   add_action("do_start", "start");
   add_action("do_read", "read");
   add_action("do_apply", "apply");

   tp = this_player();
   old_stat = tp->query_stat(SS_LAYMAN);
   tp->update_stat(SS_LAYMAN);
   new_stat = tp->query_stat(SS_LAYMAN);

   if (new_stat > old_stat && ((new_stat % 3) == 0))
      call_out("tell_player",1,tp->query_real_name());
}

void
reset_room()
{
   if (!present("statuette"))
      clone_object(STATUETTE)->move(this_object());
   if (!present("party_hat"))
      clone_object(OPEN_DIR + "party/party_hat")->move(this_object());
}

int
do_read(string str)
{
   if (str != "sign")
   {
      notify_fail("Read what?\n");
      return 0;
   }

   write("This is what you can do in this room:\n\n"
    + "  learn <skill>        Learn a skill\n"
    + "  improve <skill>      Improve a skill\n"
    + "  meditate             Alter your learning preferences\n"
    + "  start here           Change your startup place to this location.\n"
    + "  apply for Council    Apply for the Council of the Hin Warriors.\n");
   return 1;
}

int
do_apply(string str)
{
   notify_fail("Apply for what?\n");

   if (!str)
      return 0;

   str = lower_case(str);
   
   if (str != "council" && str != "for council")
      return 0;

   /* See if it is of any use */
   if (SHIRE_COUNCIL->query_council_full())
   {
      write("It is of no use to apply; there are no vacancies in the Council.\n");
      return 1;
   }

   /* Okay, apply for membership of the Council */
   SHIRE_COUNCIL->apply_for_council(this_player()->query_real_name());
   write("You have applied for membership of the Council.\n"
    + "Please be patient; enough members of the Council have to vote on it.\n");
   return 1;
}

void
tell_player(string who)
{
   if (who)
       find_player(who)->catch_msg("You have gained a new guild title!\n");
}

/*
 * Function name:   try_east
 * Description:     Low mortals may not go east, wizards and high Hins may.
 * Returns:	    1 if the way is to be blocked, 0 otherwise
 */
int
try_east()
{
   seteuid(getuid());
   if (this_player()->query_wiz_level() ||
       (this_player()->test_bit("Shire", 0, 0) == 1 &&
        this_player()->query_base_stat(SS_LAYMAN) > 30))
   {
      write("You wiggle yourself through the forcefield.\n");
      if(this_player()->short())
         say(QCTNAME(this_player()) + " wiggles through the forcefield.\n");
      return 0;
   }
   write("The forcefield bars your way.\n");
   return 1;
}

/*
 * Function name:   try_north
 * Description:     Only allow members of the Council to go north.
 * Returns:	    1 if the way is to be blocked, 0 otherwise
 */
int
try_north()
{
   seteuid(getuid());

   if (SHIRE_COUNCIL->is_council_member(this_player()->query_real_name()))
   {
      write("You wiggle yourself through the forcefield.\n");

      if(this_player()->short())
         say(QCTNAME(this_player()) + " wiggles north through the forcefield.\n");

      return 0;
   }

   write("The forcefield bars your way.\n");
   return 1;
}


/*
 * Function name:   do_start
 * Description:     Allow the players to start here for the rest of their
 *		    lives.
 * Arguments:	    str: Must be "here" or else, the function will fail.
 * Returns:	    1 if str was "here", 0 otherwise
 */
int
do_start(string str)
{
   if (str != "here")
   {
      notify_fail("Start where?\n");
      return 0;
   }

   /* Only members of our guild may */
   if (this_player()->test_bit("Shire", 0, 0) == 1)
   {
      this_player()->set_default_start_location(file_name(this_object()));
      write("From now on you will start here when you enter the game.\n");
      return 1;
   }
   else
   {
      notify_fail("But you are no true Hin Warrior!\n");
      return 0;
   }
}


/*
 * Function name:   set_up_skills
 * Description:     Define the skills, the skilltexts and the maximum level
 *		    to which the skills can be trained here.
 */
void
set_up_skills()
{
    string me, ot;

    /* Some fighter skills */
    me = "defend yourself"; ot = "use defence skill";
    sk_add_train(SS_DEFENCE,
		 ({me, ot}),0,0,
		 40);

    /* Some magical skills */
    /*
     * Note that the maxima of the FORM and ELEMENT skills are
     * set here, but really determined in sk_query_max().
     * In reality they cannot add up to more than 200, and
     * cannot get higher than the max defined here.
     *
     * Technically, a layman guild may not offer more than 50%
     * raise in any skill, but by combining these 6 skills together,
     * and limiting the total raise to 200%, we end up offering
     * an average raise of 33% per skill. The maximum of 70% is
     * still much below the 100% a occupational guild may offer.
     */ 
    me = "ability to use spellcraft"; ot = me;
    sk_add_train(SS_SPELLCRAFT,
		 ({me, ot}),0,0,
		 50);
 
    me = "ability to use conjuration spells"; ot = me;
    sk_add_train(SS_FORM_CONJURATION,
		 ({me, ot}),0,0,
		 70);
    me = "ability to use abjuration spells"; ot = me;
    sk_add_train(SS_FORM_ABJURATION,
		 ({me, ot}),0,0,
		 70);
    me = "ability to use enchantment spells"; ot = me;
    sk_add_train(SS_FORM_ENCHANTMENT,
		 ({me, ot}),0,0,
		 70);
    me = "ability to use transmutation spells"; ot = me;
    sk_add_train(SS_FORM_TRANSMUTATION,
		 ({me, ot}),0,0,
		 70);
    me = "ability to use life spells"; ot = me;
    sk_add_train(SS_ELEMENT_LIFE,
		 ({me, ot}),0,0,
		 70);
    me = "ability to use earth spells"; ot = me;
    sk_add_train(SS_ELEMENT_EARTH,
		 ({me, ot}),0,0,
		 70);
    me = "appraise monsters"; ot = me;
    sk_add_train(SS_APPR_MON,
		 ({me, ot}),0,0,
		 25);
    me = "appraise objects"; ot = me;
    sk_add_train(SS_APPR_OBJ,
		 ({me, ot}),0,0,
		 27);

    /* On general request... */
    me = "mastering the herblore"; ot = me;
    sk_add_train(SS_HERBALISM,
		 ({me, ot}),0,0,
		 44);
    me = "ability to understand languages"; ot = me;
    sk_add_train(SS_LANGUAGE,
		 ({me, ot}),0,0,
		 32);
    me = "sense of location"; ot = me;
    sk_add_train(SS_LOC_SENSE,
		 ({me, ot}),0,0,
		 18);
}

/*
 * Function name:   sk_query_max
 * Description:     Returns the maximum level to which a certain skill can
 *		    be raised by a certain player. This is dependent of the
 *		    level within our guild. There are 6 magical skills that
 *		    can be raised here, the sum of which can never exceed
 *		    (6*guild_stat) + 1. In other words, the average of the
 *		    skills will be the value of the guild_stat. This allows
 *		    people to become good at one thing, while being bad at
 *		    another.
 * Arguments:	    snum: The number of the skill that is to be raised.
 * Returns:	    The maximum or 0 if there is no maximum.
 */
int
sk_query_max(int snum)
{
    int guild_stat, i, guild_max, official_max, sk_lev, sum;
    object tp;

    tp = this_player();

    if (member_array(snum, GUILD_STAT_SKILLS) >= 0)
    {
	sum = 0;
	if ((sk_lev = tp->query_skill(SS_FORM_CONJURATION)) >= 0)
	    sum += sk_lev;
	if ((sk_lev = tp->query_skill(SS_FORM_ABJURATION)) >= 0)
	    sum += sk_lev;
	if ((sk_lev = tp->query_skill(SS_FORM_TRANSMUTATION)) >= 0)
	    sum += sk_lev;
	if ((sk_lev = tp->query_skill(SS_FORM_ENCHANTMENT)) >= 0)
	    sum += sk_lev;
	if ((sk_lev = tp->query_skill(SS_ELEMENT_LIFE)) >= 0)
	    sum += sk_lev;
	if ((sk_lev = tp->query_skill(SS_ELEMENT_EARTH)) >= 0)
	    sum += sk_lev;

	guild_stat = tp->query_base_stat(SS_LAYMAN);
	if (guild_stat < 0)
	    guild_stat = 0;
	if (guild_stat > 100)
	    guild_stat = 100;
	/*
	 * Why 2? Well, there are 6 affected spellskills, and I want thet
	 * people to be able to advance their spells up to 1/3rd of the
	 * maximum, on avarage. If all spells are raised equally, and the
	 * guild stat is at 100, they will all be 33.
         */
	guild_max = (2 * guild_stat) + 1 - sum;
        if (guild_max < 1)
	    guild_max = 1;
    }
    else
	guild_max = 100; /* Set to something high, so the official max goes */

    official_max = ::sk_query_max(snum);

    if (guild_max <= official_max)
	return guild_max;
    else
	return official_max;
}

int
sk_improve(string str)
{
    /* Is the player a guildmember? */
    if (!(this_player()->test_bit("Shire", 0, 0)))
    {
	write("Only members of the Shire-guild can do that here!\n");
	return 1;
    }
    return ::sk_improve(str);
}
