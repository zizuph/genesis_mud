/* chapel/obj/cwand.c is cloned by chapel/jewelers.c */
inherit "/std/object";
 
#include "../chapel.h"
#include <stdproperties.h>
#include <const.h>
#include <macros.h>
#include <cmdparse.h>
 
#define   PLACES   ({ CHAPEL_DIR, VILLAGE_DIR })
 
string groom, bride;

/* Prototypes */
int ring(string str);
int pron(string arg);
int eject(string str);
 
void
create_object()
{
    set_name("wand");
    add_name("_emerald_chapel_mc_wand");
    add_adj("ceremonial");
    set_long("This is a clear crystal wand that is given to the " +
       "master of the wedding ceremony.  The master can: \n" +
       "pronounce (pronounces the couple husband and wife),\n"+
       "ring bells (rings the church bells at end of ceremony),\n" +
       "eject (eject an unwanted individual from the chapel).\n");
 
    add_prop(OBJ_I_VOLUME, 250);
    add_prop(OBJ_I_WEIGHT, 450);
    add_prop(OBJ_M_NO_DROP, 1);
}
 
void
init()
{
    ::init();
    add_action(ring, "ring");
    add_action(pron, "pronounce");
    add_action(eject, "eject");
}
 
void
enter_env(object env, object from)
{
    object podium;
 
    ::enter_env(env, from);
    if (living(env) && environment(env) && environment(env)->is_chapel()) {
     podium = present("podium", environment(env));
     if (podium)
     podium->living_entered(env);
    }
}
 
void
leave_env(object env, object to)
{
    object podium;
 
    ::leave_env(env, to);
    if (living(env) && environment(env) && environment(env)->is_chapel()) {
     podium = present("podium", environment(env));
     if (podium)
         podium->living_left(env);
    }
}

int
eject(string str)
{
    object *oblist;
    if (!strlen(str) ||
        !sizeof(oblist = PARSE_THIS(str, "[the] %l")))
    {
        notify_fail("Eject whom?\n");
        return 0;
    }

    if (!environment(this_player())->is_chapel())
    {
        write("You aren't in the chapel, though.\n");
        return 1;
    }

    if (sizeof(oblist) > 1)
    {
        write("Be more specific!  You can only eject one person " +
            "at a time.\n");
        return 1;
    }

    oblist[0]->add_prop(THROWN_OUT,
        oblist[0]->query_prop(THROWN_OUT) + 1);

    oblist[0]->catch_tell("You are ejected from the chapel!\n");
    write("You eject " + 
        oblist[0]->query_the_name(this_player()) + ".\n");
    say(QCTNAME(oblist[0]) + " is ejected from the chapel!\n",
        ({ this_player(), oblist[0] }));
    oblist[0]->move_living("X", CHAPEL_DIR + "outside");
    return 1;
}

int
pron(string arg)
{
    object *p1, *p2, bag, ring;
    string str, dummy;
    int genders;
    object bride_ob, groom_ob;


    if (arg)
    {
       notify_fail("Pronounce what?\n");       
       return 0;
    }

    bride_ob = find_player(bride);
    groom_ob = find_player(groom);

    if (!bride_ob || !present(bride_ob, environment(this_player())))
    {
        write("The bride isn't present.\n");
        return 1;
    }

    if (!groom_ob || !present(groom_ob, environment(this_player())))
    {
        write("The groom isn't present.\n");
        return 1;
    }

    if (groom_ob == bride_ob)
    {
        return 0;
    }

    if (!environment(this_player())->is_chapel()) 
    {
       write("You must be in the wedding chapel to do that.\n");
       return 1;
    }

    genders = (1 << groom_ob->query_gender()) | (1 << bride_ob->query_gender());
 
    if (groom_ob->query_linkdead()) 
    {
        this_player()->catch_msg(QCTNAME(groom_ob) + " is linkdead.\n");
        return 1;
    }

    if (bride_ob->query_linkdead()) 
    {
        this_player()->catch_msg(QCTNAME(bride_ob) + " is linkdead.\n");
        return 1;
    }

    if (!groom_ob->query_prop(PLAYER_I_IS_GETTING_MARRIED))
    {
        write(groom_ob->query_The_name(this_player()) +
            " isn't prepared!\n");
        return 1;
    }

    if (!bride_ob->query_prop(PLAYER_I_IS_GETTING_MARRIED))
    {
        write(bride_ob->query_The_name(this_player()) +
            " isn't prepared!\n");
        return 1;
    }

    if (groom_ob == this_player() || bride_ob == this_player()) 
    {
    	write("You cannot be your own ceremonial master!\n");
    	return 1;
    }

    if (groom_ob->query_wiz_level() > this_player()->query_wiz_level()) 
    {
    	this_player()->catch_msg("You are not empowered to marry " +
      	    QTNAME(groom_ob) + " anyone.\n");
    	return 1;
    }

    if (bride_ob->query_wiz_level() > this_player()->query_wiz_level()) 
    {
    	this_player()->catch_msg("You are not empowered to marry " +
    	    QTNAME(bride_ob) + " anyone.\n");
    	return 1;
    }

    p1 = FIND_STR_IN_OBJECT("ring bag", this_player());
    if (!sizeof(p1))
    {
        write("You don't have the bag holding the marriage rings!\n");
        return 1;
    }

    bag = p1[0];
    p2 = FIND_STR_IN_OBJECT("marriage rings", bag);
    if (sizeof(p2) != 2) 
    {
    	write("The ring bag doesn't hold two rings!\n");
    	return 1;
    }

    if (!(genders & (1 << G_FEMALE)) || !(genders & (1 << G_MALE)))
    {
    	this_player()->catch_msg("You pronounce " + QTNAME(groom_ob) + " and "+
    		  QTNAME(bride_ob) + " married.\n");

    	say(QCTNAME(this_player()) + " pronounces " + QTNAME(groom_ob) + " and "+
    	     QTNAME(bride_ob) + " married.\n",
    	       ({ this_player(), groom_ob, bride_ob }));
    	groom_ob->catch_msg(QCTNAME(this_player()) + " pronounces you and "+
    	     QTNAME(bride_ob) + " married.\n");
    	groom_ob->catch_msg("You may kiss " + bride_ob->query_the_name(groom_ob) + ".\n");
    	bride_ob->catch_msg(QCTNAME(this_player()) + " pronounces " + QTNAME(groom_ob) +
    	  " and you married.\n");
    }
    else
    {
    	this_player()->catch_msg("You pronounce " + QTNAME(groom_ob) + " and "+
    		  QTNAME(bride_ob) + " to be husband and wife.\n");
    	say(QCTNAME(this_player()) + " pronounces " + QTNAME(groom_ob) + " and "+
    	     QTNAME(bride_ob) + " to be husband and wife.\n",
    	       ({ this_player(), groom_ob, bride_ob }));
    	groom_ob->catch_msg(QCTNAME(this_player()) + " pronounces you and "+
    	     QTNAME(bride_ob) + " to be husband and wife.\n");
    	groom_ob->catch_msg("You may kiss the bride.\n");
    	bride_ob->catch_msg(QCTNAME(this_player()) + " pronounces " + QTNAME(groom_ob) +
    	  " and you to be husband and wife.\n");
    }

    groom_ob->remove_prop(IS_GROOM);
    bride_ob->remove_prop(IS_BRIDE);
    groom_ob->remove_prop(PLAYER_I_IS_GETTING_MARRIED);
    bride_ob->remove_prop(PLAYER_I_IS_GETTING_MARRIED);
    groom_ob->add_prop(JUST_MARRIED, 1);
    bride_ob->add_prop(JUST_MARRIED, 1);
    bag->remove_prop(CONT_M_NO_REM);
    M_MANAGER->wed(groom_ob->query_real_name(), bride_ob->query_real_name(),
                   p2[0]->query_material());
    p2[0]->set_person(groom_ob->query_real_name());
    p2[0]->move(bride_ob);
    p2[1]->set_person(bride_ob->query_real_name());
    p2[1]->move(groom_ob);
    bag->remove_object();
    return 1;
}
 
int
hear_bells(object ob)
{
    string place, *p;
 
    if (environment(ob))
       place="" + MASTER_OB(environment(ob));
    else
       return 0;
    p = explode(place + "/", "/");
    if (sizeof(p) < 2)
      place = "/" + p[0];
    else
       place = "/" + implode(p[0..sizeof(p)-2], "/");
    if (member_array(place, PLACES) >= 0)
       return 1;
    return 0;
}
 
int
ring(string str)
{
    object *player;
    int    i;
 
    notify_fail("Ring what?\n");
    if (str!="bells" && str!="church bells")
        return 0;
    notify_fail("You have to be in the chapel to do that.\n");
    if (!environment(this_player())->is_chapel())
        return 0;
    write("You ring the church bells.\n");
    say(({ this_player()->query_met_name() + " rings "+
       "the church bells which peal their music throughout the "+
       "lands, signifying the end of the wedding and the start "+
       "of the celebration.\n",
        this_player()->query_nonmet_name() + " rings "+
       "the church bells which peal their music throughout the "+
       "lands, signifying the end of the wedding and the start "+
       "of the celebration.\n"}));
    player = users();
    for (i=0 ; i<sizeof(player) ; i++)
    if (player[i] && !present(player[i], environment(this_player())))
         if (hear_bells(player[i]))
     player[i]->catch_msg("You can hear some bells ringing, "+
          "signifying a wedding.\n");
    return 1;
}
 
void
set_groom(string str)
{
    groom = str;
}
 
void
set_bride(string str)
{
    bride = str;
}
