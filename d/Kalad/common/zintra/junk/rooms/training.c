inherit "/std/room.c";
inherit "/lib/guild_support";
inherit "/lib/skill_raise";

#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include <language.h>
#include "../defs.h"

#define CLOSED          0       /* 1 = closed,   0 = open.  */

void set_up_skills();
void rise();
int catch_all(string str);

int closed;
object meditate;

void
reset_room()
{
    if (!present("master"))
    room_add_object(G_MON + "master2");
}

void
create_room()
{
    closed = CLOSED;
    set_short("Training Hall");
    set_long(BS(
"Among the debris lie many practice weapons, fake doors, safes, and " +
"many other pieces of training equipment.  Anything a thief could possibly " +
"need to improve his or her skills is here in one form or another.\n"));

    add_exit(G_ROOMS + "ghall2", "west", 0);

    add_item(({"lanterns", "lantern"}), BS(
"They are rusty, smoky, and in great need of more oil.  Unfortuantely for " +
"you, they are firmly attached to the wall.\n"));

    INSIDE
    create_guild_support();
    create_skill_raise();
    set_up_skills();

   reset_room();
}

void
init()
{
    add_action("hypno_hook", "hypno");
    add_action("hypno_hook", "hypnotize");
    init_skill_raise();
    ::init();
}

int
hypno_hook(string str)
{
    if (!present("master"))
    {
    write ("The master is not here.  There is no one to hypnotize you.\n");
    return 1;
    }
   if (!str || str == "me" || str == "myself")
    {
        if (MEMBER(TP))
        {
            if (TP->query_prop(LIVE_I_MEDITATES))
            {
                write(gs_hook_already_meditate());
                return 1;
            }
            return gs_meditate(str);
        }
    write("The master says: I'm sorry, I will only do that for " +
        "guild members.  Perhaps you should join?\n");
    return 1;
    }
    NF("What is it that your trying to do?\n");
    return 0;
}

varargs int
gs_meditate(string str)
{
    ::gs_meditate(str);
    TP->add_prop(LIVE_S_EXTRA_SHORT, " (hypnotized)");
    return 1;
}

int
gs_hook_catch_error(string str)
{
    write("You can't do that while hypnotized.\n");
    return 1;
}

void
gs_hook_already_meditate()
{
    write(BS("You are already hypnotized. If you want to "+
          "stop, you can do so by typing 'rise'.\n"));
}

void
gs_hook_start_meditate()
{
  write(BS("The master pulls out a gold ring on a chain.  He starts "+
        "to swing the ring in front of your eyes while speaking " +
        "to you in a low, soft voice.  Soon your mind starts to "+
        "clear, and you reach deep within the receses of your mind.  "+
        "You find yourself able to <estimate> your different "+
        "preferences and <set> them at your own desire. Just <rise> "+
        "when you wish to break this trance.\n"));
}

void
gs_hook_rise()
{
  write(BS ("As if ascending from a great depth, you rise to the "+
        "surface of your consciousness. You exhale and feel " +
        "very relaxed.\n"));
}

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    if (!interactive(ob) || !closed) return;
    if (ob->query_wiz_level())
    write("\n\nWARNING!\nYou shouldn't be here. "+
          "I'm doing some work on the guild.\n");
  else
    {
        write("The guild is closed. Come back later.\n");
        ob->move(G_ROOMS + "ghall2");
    }
}

string
close_guild()
{
    if (closed)
    {
        closed = 0;
        return "  **The training room is now open**";
    }
    closed = 1;
    return "  **The training room is now closed**";
}

int
query_closed()
{
    return closed;
}

void
set_up_skills()
{
    string me;

    me = "use a sword";
    sk_add_train(SS_WEP_SWORD, ({ me, me }), 0,0, 60);
    me = "use a knife";
    sk_add_train(SS_WEP_KNIFE, ({ me, me }), 0,0, 100);
    me = "fight while unarmed";
    sk_add_train(SS_UNARM_COMBAT,  ({ me, me }), 0,0, 50);
    me = "fight while blind";
    sk_add_train(SS_BLIND_COMBAT, ({me, me}), 0, 0, 50);
    me = "parry the attacks of others";
    sk_add_train(SS_PARRY, ({ me, me }), 0,0, 50);
    me = "defend yourself in a fight";
    sk_add_train(SS_DEFENCE, ({ me, me }), 0,0, 50);
    me = "pick locks of all sorts";
    sk_add_train(SS_OPEN_LOCK, ({ me, me }), 0,0, 100);
    me = "steal from the unwary";
    sk_add_train(SS_PICK_POCKET, ({ me, me }), 0,0, 100);
    me = "perform acrobatics";
    sk_add_train(SS_ACROBAT, ({ me, me }), 0,0, 100);
    me = "locate and disarm traps set by others";
    sk_add_train(SS_FR_TRAP, ({ me, me }), 0,0, 100);
    me = "move siliently and sneaky";
    sk_add_train(SS_SNEAK, ({ me, me }), 0,0, 100);
    me = "hide from the unaware";
    sk_add_train(SS_HIDE, ({ me, me }), 0,0, 100);
    me = "injure others from behind";
    sk_add_train(SS_BACKSTAB, ({ me, me }), 0,0, 100);
    me = "properly evaluate your enemy";
    sk_add_train(SS_APPR_MON, ({ me, me }), 0,0, 50);;
    me = "determine the value of an object";
    sk_add_train(SS_APPR_OBJ, ({ me, me }), 0,0, 50);
    me = "to corectly assess the properties of an object";
    sk_add_train(SS_APPR_VAL, ({ me, me }), 0,0, 50);
    me = "to climb all sorts of things";
    sk_add_train(SS_CLIMB, ({ me, me }), 0,0, 50);
    me = "to keep track of your location";
    sk_add_train(SS_LOC_SENSE, ({ me, me }), 0,0, 50);
    me = "to track others";
    sk_add_train(SS_TRACKING, ({ me, me }), 0,0, 50);
    me = "understand foreign languages";
    sk_add_train(SS_LANGUAGE, ({ me, me }), 0,0, 50);
    me = "to be aware of your surroundings";
    sk_add_train(SS_AWARENESS, ({ me, me }), 0,0, 50);
    me = "to con shopkeepers and banks";
    sk_add_train(SS_TRADING, ({ me, me }), 0,0, 50);
}

int
sk_improve(string str)
{
    if (!present("master"))
    {
        write("The master is not here.  There is no one to teach you.\n");
        return 1;
    }
    if (!MEMBER(TP))
    {
        NF("The Master says: I'm sorry.  I may only teach the Blackhands.\n");
        if (str) return 0;
        write(BS("The Master says: I'm sorry, but I may only teach the "+
            "Blackhands.  Perhaps you should consider joining?  Let me " +
            "show you the skills I can provide.\n"));
    }
    return ::sk_improve(str);
}

int
sk_hook_improved_max(string skill)
{
    NF(BS("The Master has taught you all that he knows in that area.\n"));
    return 0;
}

int
sk_hook_no_list_improve()
{
    write(BS("The Master has taught you all that he knows in that area.  "+
        "'Go out and seek the world, my desciple,' he says.  'Perhaps " +
           "there are others who can teach you more.'\n"));
    return 1;
}

void
sk_hook_raise_rank(int snum, int to_lev, int cost)
{
    string rank, long_str;
    rank = sk_rank(to_lev);
    TP->catch_msg("The Master improves your ability to "+
        sk_tdesc[snum][0] + ".\n");
    write("You achieve the rank of " + rank + ".\n");
    say(BS("The Master improves " + QTNAME(TP) + "'s ability to "+
        sk_tdesc[snum][1] + ", and " + TP->query_pronoun() + " receives "+
        "the rank of " + rank + ".\n"));
}

