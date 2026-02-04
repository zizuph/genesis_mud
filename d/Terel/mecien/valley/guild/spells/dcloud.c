/* Creative rights reserved to Mecien (Jeff Babcock) and team. */
/*
 * Dust cloud
 */
inherit "/std/creature";
inherit "/std/combat/unarmed";

#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>
#include <ss_types.h>
#include "/d/Terel/common/terel_defs.h"

#define TO            this_object()
#define TP            this_player()
#define STD_SOUL      "/cmd/std/soul_cmd"
#define SOULS         ({"social", "state", "things"})
#define ANIMAL_SOUL   "/d/Terel/mecien/valley/guild/spells/soul_dust"


#define H_HEAD  0
#define H_BODY  1
#define H_LEGS  2

private object npc_link;

void set_player_link(object player, object control);
void set_up_player_values();
object query_player_link();

public void
create_creature()
{
    set_name("cloud");
    set_short("shifting dust cloud");
    set_long("A dark, shifting, cloud of dust.\n");
    set_adj(({"shifting", "dust"}));
    set_race_name("cloud");

   set_gender(2);
   set_stats(({ 0, 0, 0, 0, 0, 0 }));

  add_prop(NPC_I_NO_LOOKS, 1);
   add_prop(OBJ_M_NO_ATTACK, "It is futile.\n");
}

/*
 * Function name: set_player_link
 * Description:   Links a player to the output of the mobile
 * Arguments:     player: Player to link mobile to
 *                control: Object controlling the link
 */
void
set_player_link(object player, object control)
{
    if (!living(player) || npc_link) return;

    control->set_npc(TO);
    npc_link = control;
    control->move(player);
    set_alarm(1.0, -1.0, set_up_player_values);
}

/*
 * Description: Return the pointer to the current controller
 */
object
query_player_link() { return npc_link; }

/*
 *  Description: For monster link purposes
 */
void
catch_tell(string str)
{
    if (npc_link) npc_link->link_intext(str);
    ::catch_tell(str);
}

/*
 * Description: set up some values depending on player
 */
void
set_up_player_values()
{
    int i;
    object player;

    if (!npc_link) return;
    player = environment(npc_link);
    if (!living(player)) return;
    
    TO->set_alignment(player->query_alignment());
    TO->remove_cmdsoul(STD_SOUL);
    TO->add_cmdsoul(ANIMAL_SOUL);
    for (i=0; i<sizeof(SOULS); i++) add_cmdsoul("/cmd/live/"+SOULS[i]);
    TO->update_hooks();
}

public void
do_die(object killer)
{
    if (query_hp() > 0) return;
    if (npc_link) npc_link->link_monster_died(killer);
    ::do_die(killer);
}

public int
query_met(mixed name)
{
    return 0;
}
