/*
 * Copyright (C) 14-December-2000 by Shadow DeForest.
 *
 * Creator  : Shadowlynx
 * Date     : 14-December-2000
 * Filename : adv_guild.c
 * Purpose  : This is the Adventurer Guild in the Traveller Camp.
 * Credits  : Modified from the original file of
 *              1. </d/Genesis/start/human/town/adv_guild.c>
 *                 by Styles - January, 1992.
 * Includes : Meditation.
 *            Set preferences.
 *            List guilds.
 *            Train general skills.
 *            Self restriction.
 * Updates  : 
 */

#pragma save_binary
#pragma strict_types

inherit "/lib/guild_support"; 
inherit "/lib/skill_raise";
inherit "/std/room";

#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>

#include "../defs.h"

/* Prototypes */
void set_up_skills();
void reset_room();

/* variables */
object box;

void
create_room()
{
    set_short("Sparkle Adventurer Guild");
    set_long("Welcome to the Sparkle Adventurer Guild.\n\n" +
      "Soft shadows flicker along the walls in the wavering" +
      " light of four blazing torches, one in each corner of the" +
      " room. Ornate wall sconces carved to look like dragon" +
      " claws hold each torch firmly in place. A number of" +
      " trophies adorn the walls which have been brought back" +
      " to the guild hall by bold adventurers. An age-worn" +
      " hardwood floor is mostly covered by a soft plush carpet" +
      " where many adventurers often sit down and relax.\n\n" +
      "Here an adventurer may advance their skills or set" +
      " personal priorities. You can choose to <meditate> and" +
      " reset your preferences. Additionally, you can <learn>" +
      " new skills or <improve> the ones you already have. With" +
      " <list guilds> you can find out information about the" +
      " guilds you are a member of.\n");

    add_item(({"box","charity box"}),"Donations of excess equipment or" +
      " items may be placed into this box for anyone to use if they" +
      " have need.\n");
    add_item(({"shadows","soft shadows"}),"Faint outlines almost like" +
      " wisps of dark smoke flicker along the walls lending images" +
      " to the imagination like clouds in the sky.\n");
    add_item(({"light","wavering light"}),"Four blazing torches in" +
      " each corner of the room cast a soft, subdued wavering light" +
      " around the room.\n");
    add_item(({"torch","torches","blazing torch","blazing torches"}),
      "In each corner of the room is a blazing torch held firmly in" +
      " place by an ornate wall sconce carved to imitate the claws" +
      " of a dragon.\n");
    add_item(({"sconce","sconces","ornate sconce","ornate sconces"}),
      "Intricately carved sconces are attached to the walls in each" +
      " corner of the guild hall. They are designed to appear like" +
      " the claws of a dragon. A blazing torch rests firmly in each" +
      " set of claws.\n");
    add_item(({"wall","walls"}),"Several trophies adorn the walls of" +
      " the guild hall. Most have been stuffed or mounted and depict" +
      " either animals or exotic creatures which may be found within" +
      " the realms.\n");
    add_item(({"trophy","animal","creature","exotic creature"}),"There" +
      " are so many to choose from, you can't decide which one to" +
      " look at first.\n");
    add_item(({"trophies","animals","creatures","exotic creatures"}),
      "Numerous trophies decorate the walls displaying the bravery" +
      " of past adventurers. Among these trophies, you spot a black" +
      " lion perched on a large rock surveying the surroundings, a" +
      " wild boar head with huge pointed tusks and a mean looking" +
      " snout, the preserved body of a death spider spinning a silky" +
      " cocoon around its victim, the head of a ferocious red dragon" +
      " with its open mouth ready to shoot a ray of burning flames," +
      " a bestial statue of a gargoyle squatting in stony silence," +
      " the head of a frost giant with a vicious snarl on its face," +
      " the fearsome heads of a magnificent hydra all swerving to" +
      " strike at an invisible target, the body of a giant shadow" +
      " lizard stalking its prey, the stone head of a medusa with" +
      " its hair a mass of wriggling snakes, the massive head of a" +
      " minotaur supporting a full set of horns, the body of a" +
      " giant octopus with each of its eight tentacles creeping along" +
      " the floor seeking a quarry, the graceful body of a snow wolf" +
      " scanning the area for its next kill, the coiled body of a wyrm" +
      " with its wings outstretched, and the unmistakable form of a" +
      " dogcow staring at you with sweet innocent eyes.\n");
    add_item(({"lion","black lion","lion perched on a rock",
	"lion perched on a large rock","rock","large rock",
	"black lion perched on a large rock",
	"black lion perched on a rock"}),
      "In one corner of the room underneath a blazing torch" +
      " a sleek black lion is perched on a large rock. Its" +
      " shiny dark eyes gaze intently at the surroundings." +
      " A bushy black mane creates a dark halo around its" +
      " head. Its regal and majestic stature also suggests" +
      " a cunning yet furtive grace. It is not known whether" +
      " black lions are the result of wizard experiments or" +
      " natural cross-breeding in the wild. What is certain," +
      " is that they are a cross between a black panther and" +
      " a lion, a mix that makes them the most savage of all" +
      " the hunting cats. Black lions are among the most deadly" +
      " of predators.\n");
    add_item(({"boar","wild boar","boar head","wild boar head",
	"tusks","pointed tusks","huge pointed tusks","snout",
	"mean snout","mean looking snout","huge tusks"}),
      "This is the head of a wild boar. Huge pointed tusks" +
      " protrude from under a mean looking snout. Wild boars" +
      " are hunted for their choice meat and pelts which can" +
      " fetch a small fortune in gold. They look like huge pigs" +
      " covered in tangled clumps of coarse reddish-brown hair." +
      " They are brutish, aggressive beasts and will stand and" +
      " fight with their tusks in an almost savage fury.\n");
    add_item(({"carpet","plush carpet","soft carpet",
	"soft plush carpet"}),"A soft plush carpet covers most of the" +
      " age-worn hardwood floor. It looks very comfortable to rest on." +
      " Most people tend to sit down and meditate in the soft luxery" +
      " of this soft carpet.\n");
    add_item(({"floor","flooring","hardwood floor","hardwood flooring",
	"age-worn floor","age-worn flooring","age-worn hardwood floor",
	"age-worn hardwood flooring"}),"Beneath the soft plush carpet" +
      " is an age-worn hardwood floor. Several spots are scuffmarked" +
      " by the heavy treads of countless visitors to the guild hall.\n");

    add_exit(TOWN_DIR + "road3","north",0,0,0);

    add_prop(OBJ_S_WIZINFO, "@@wizinfo");
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);

    box = clone_object(OBJ_DIR + "box");
    box->set_long("This is a large box where donations of excess" +
      " equipment or items may be placed for anyone to use.\n");
    box->move(this_object());

    reset_room();

    create_skill_raise();
    set_up_skills();
}

void
reset_room()
{
    int i;

    if (!box || present("dagger", box))
	return;

    for(i = 0; i < 4; i++)
	clone_object(OBJ_DIR + "dagger")->move(box);
}

void
leave_inv(object ob, mixed to)
{
    ::leave_inv(ob, to);
    gs_leave_inv(ob, to);
}

void
set_up_skills()
{
    string me, ot;

    me = "fight unarmed"; ot = me;
    sk_add_train(SS_UNARM_COMBAT,  ({ me, ot }),     0, 0, 30 );
    me = "defend yourself"; ot = "use defence skill";
    sk_add_train(SS_DEFENCE,  ({ me, ot }),     0, 0, 20 );
    me = "use a sword"; ot = me;
    sk_add_train(SS_WEP_SWORD,  ({ me, ot }),     0, 0, 30 );
    me = "use a knife"; ot = me;
    sk_add_train(SS_WEP_KNIFE,  ({ me, ot }),     0, 0, 30 );
    me = "use a club"; ot = me;
    sk_add_train(SS_WEP_CLUB,   ({ me, ot }),       0, 0, 30 );
    me = "use spellcraft"; ot = me;
    sk_add_train(SS_SPELLCRAFT, ({ me, ot }),    0, 0, 20 );
    me = "appraise the quality of different objects"; ot = me;
    sk_add_train(SS_APPR_OBJ,	({ me, ot }),      0, 0, 30 );
    me = "appraise the value of different objects"; ot = me;
    sk_add_train(SS_APPR_VAL,	({ me, ot }), 0, 0, 30 );
    me = "swim"; ot = me;
    sk_add_train(SS_SWIM,  ({ me, ot }), 0, 0, 30 );
    me = "climb"; ot = me;
    sk_add_train(SS_CLIMB, ({ me, ot }), 0, 0, 30 );
    me = "hunt wild game"; ot = me;
    sk_add_train(SS_HUNTING,	({ me, ot }), 0, 0, 30 );
    me = "be aware of your surroundings"; ot = "his awareness";
    sk_add_train(SS_AWARENESS, ({ me, ot }),     0, 0, 30 );
    me = "trade and make deals"; ot = me;
    sk_add_train(SS_TRADING,	({ me, ot }),       0, 0, 30 );
    me = "ride a horse"; ot = me;
    sk_add_train(SS_RIDING,       ({ me, ot }),       0, 0, 30 );
}

void
init()
{
    ::init();

    init_skill_raise();
    init_guild_support();
}
