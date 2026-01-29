 /*
 * /w/novo/open/auction/fake_item.c
 *
 * This is the fake item in the quest auction.
 *
 * Created March 2008, by Novo
 *
 *
 */
#pragma strict_types

inherit "/std/object";

#include <cmdparse.h>
#include <language.h>
#include <ss_types.h>
#include <stdproperties.h>
#include "../defs.h"; 

public void
create_object()
{

   set_name("fakeitem");
   set_short("fake item");
   
   set_long("This is a fake item.\n");
}


public void configure_for_player(object player)
{
    if (player->query_skill(SS_WEP_SWORD)>=75)
    {
        set_short("basket-hilt falchion");
        set_name("falchion");
        set_adj(({"basket-hilt", "broad", "basket", "hilt"}));
        set_long("A handsome, broad sword of medium length with a gently "+
        "curving edge.  The steel blade is vaguely sickle-shaped, double-"+
        "edged, and has a tapering point, making it effective as both a "+
        "cutting and thrusting weapon.  Crimson and black silk laces are "+
        "braided around the steel handle, which is long enough to fit two "+
        "hands.  The pommel is fitted with an incredibly detailed golden "+
        "spider whose arching legs secure it to the handle.  A basket-hilt "+
        "of gold-plated steel has been woven in an elaborate web of "+
        "surprising beauty and functionality.\n   "+
        "Some runes have been etched into the blade, near the hilt.\n"+
        "It looks like it is in prime condition.\n");
        return;
    }
    if (player->query_skill(SS_WEP_AXE)>=75)
    {
        set_short("unholy crystal axe");
        set_name("axe");
        set_adj(({"unholy","crystal"}));
        set_long("The unholy crystal axe is a very large axe made out of "+
        "the purest crystal. The blade itself looks almost as clear as "+
        "glass, and as your hand glides over the blade you can feel some "+
        "words or runes carved into it. The shaft is likewise "+
        "constructed out of the same material, giving the impression "+
        "that the entire weapon has been made out of one solid block of "+
        "crystal. Around the hilt some soft leather has been wrapped to "+
        "protect the wielder and give a better grip around the axe. As "+
        "you hold the weapon in the air  you notice an evil aura "+
        "surrounding the blade.\n"+
        "It looks like it is in prime condition.\n");
        return;
    }
    if (player->query_skill(SS_WEP_CLUB)>=75)
    {
        set_short("bloody skull club");
        set_name("club");
        set_adj(({"bloody","skull"}));
        set_long("This large club has a bloody skull from a monster "+
        "possibly a goblin. The eye socktes, hollow and utter black, "+
        "seems to be staring at you. The fangs of the skull function "+
        "as spikes to rip deeply into opponents in battle. The long "+
        "handle is made of a gnarled dark root of what must have "+
        "been a very large tree.\n"+
        "It looks like it is in prime condition.\n");
        return;
    }
    if (player->query_skill(SS_WEP_POLEARM)>=75)
    {
        set_short("strange halberd");
        set_name("halberd");
        set_adj(({"strange"}));
        set_long("This is very strange halberd. Maybe it should be a "+
        "good weapon but you simply can't hit properly with it.\n"+
        "It looks like it is in prime condition.\n");
        return;
    }
 
    set_short("pair of golden gauntlets");
    set_name("gauntlets");
    set_adj(({"gold","golden","magical"}));
    set_long("This pair of gauntlets looks like a real treasure. Each "+
    "moulded glove "+
    "is quite ornate, with sparkling jewels set within the patterns of "+
    "delicate lines etched into the gold. You marvel over the beautiful "+
    "craftmanship. \n"+
    "It looks like it is in prime condition.\n");
    return;
}