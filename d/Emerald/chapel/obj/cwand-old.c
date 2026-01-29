/* chapel/obj/cwand.c is cloned by chapel/jewelers.c */
inherit "/std/object";
 
#include "../chapel.h"
#include <stdproperties.h>
#include <const.h>
#include <macros.h>
#include <cmdparse.h>
 
#define   PLACES   ({ CHAPEL_DIR, VILLAGE_DIR, FOREST_DIR })
 
string groom, bride;

/* Prototypes */
int ring(string str);
int pron(string arg);
 
void
create_object()
{
    set_name("wand");
    add_adj("ceremonial");
    set_long("This is a clear crystal wand that allows "+
       "the person in charge of the cereomony to use the following "+
       "commands:  pronounce (pronounces the couple husband and wife), "+
       "ring bells (rings the church bells at end of ceremony).\n");
 
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
pron(string arg)
{
    object *p1, *p2, pl1, pl2, bag, ring;
    string str, dummy;
 
    notify_fail("Pronounce what?\n");
    if (arg)
       return 0;
    if (!parse_command(bride + " and " + groom, ({ environment(this_player()) }), "%l 'and' %l", pl1, pl2))
    return 0;
    if (pl1->query_gender() != G_MALE) {
    bag = pl1;
    pl1 = pl2;
    pl2 = bag;
    }
    if (pl1 == pl2)
      return 0;
    if (!environment(this_player())->is_chapel()) {
     notify_fail("You must be in the wedding chapel to do that.\n");
     return 0;
    }
    if (pl1->query_gender() != G_MALE || pl2->query_gender() != G_FEMALE) {
    write("Let's not get kinky here, ok?\n");
    return 1;
    }
    if (pl1->query_linkdead()) {
    this_player()->catch_msg(QCTNAME(pl1) + " is linkdead.\n");
    return 1;
    }
    if (pl2->query_linkdead()) {
    this_player()->catch_msg(QCTNAME(pl2) + " is linkdead.\n");
    return 1;
    }
    if (!pl1->query_prop(IS_GROOM)) {
    this_player()->catch_msg(QCTNAME(pl1) + " isn't a groom!\n");
    return 1;
    }
    if (!pl2->query_prop(IS_BRIDE)) {
    this_player()->catch_msg(QCTNAME(pl2) + " isn't a bride!\n");
    return 1;
    }
    if (pl1 == this_player() || pl2 == this_player()) {
    write("You cannot be your own ceremonial master!\n");
    return 1;
    }
    if (pl1->query_wiz_level() > this_player()->query_wiz_level()) {
    this_player()->catch_msg("You are not empowered to marry " +
    QTNAME(pl1) + " anyone.\n");
    return 1;
    }
    if (pl2->query_wiz_level() > this_player()->query_wiz_level()) {
    this_player()->catch_msg("You are not empowered to marry " +
    QTNAME(pl2) + " anyone.\n");
    return 1;
    }
    p1 = FIND_STR_IN_OBJECT("ring bag", this_player());
    if (!sizeof(p1)) {
    write("You don't have the bag holding the marriage rings!\n");
    return 1;
    }
    bag = p1[0];
    p2 = FIND_STR_IN_OBJECT("marriage rings", bag);
    if (sizeof(p2) != 2) {
    write("The ring bag doesn't hold two rings!\n");
    return 1;
    }
    this_player()->catch_msg("You pronounce " + QTNAME(pl1) + " and "+
              QTNAME(pl2) + " to be husband and wife.\n");
    say(QCTNAME(this_player()) + " pronounces " + QTNAME(pl1) + " and "+
         QTNAME(pl2) + " to be husband and wife.\n",
           ({ this_player(), pl1, pl2 }));
    pl1->catch_msg(QCTNAME(this_player()) + " pronounces you and "+
         QTNAME(pl2) + " to be husband and wife.\n");
    pl1->catch_msg("You may kiss the bride.\n");
    pl2->catch_msg(QCTNAME(this_player()) + " pronounces " + QTNAME(pl1) +
      " and you to be husband and wife.\n");
    pl1->remove_prop(IS_GROOM);
    pl2->remove_prop(IS_BRIDE);
    pl1->add_prop(JUST_MARRIED, 1);
    pl2->add_prop(JUST_MARRIED, 1);
    bag->remove_prop(CONT_M_NO_REM);
    M_MANAGER->wed(pl1->query_real_name(), pl2->query_real_name(),
                   p2[0]->query_material());
    p2[0]->set_person(pl1->query_real_name());
    p2[0]->move(pl2);
    p2[1]->set_person(pl2->query_real_name());
    p2[1]->move(pl1);
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
