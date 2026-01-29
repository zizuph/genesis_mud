
/* 
   Calian Council headquarters.

   Coded by Maniac

   History:
        4/6/2000     "remove enemy info" action removed   Maniac
        1/3/2000     updates                              Maniac
       23/1/97       added some info                      Maniac 
       4/10/96       arches allowed in                    Maniac
       31/5/96       security improved                    Maniac
       18.3.96       councilc code no longer inherited    Maniac
       22/12/95      actions for double commands added   Maniac
       27/10/95      discharge command added           Maniac
       26.6.95       Bug corrected                     Maniac
       29.3.95       Calian enemy list commands added  Maniac
       27.3.95       snoop prevented                   Maniac
*/

#pragma save_binary

inherit "/std/room";
#include <macros.h>
#include <stdproperties.h>
#include <language.h>
#include <std.h>
#include "defs.h"
#include COUNCIL_HEADER

void
load_board()
{
    clone_object(OBJECT("council_board"))->move(THIS);
}

void
load_book()
{
    clone_object(OBJECT("council_log_book"))->move(THIS);
}

int
query_prevent_snoop()
{
    return 1;
}


void 
create_room()
{
    set_short("The headquarters of the Calian Council");
    set_long(
        "The headquarters of the Calian Council, a grand room " +
            "in the palace of Caliana. " +
        "Great war shields of steel adorn the east, west and " +
            "south walls, spaced evenly as a regiment of warriors. " +
        "On the north wall a large banner hangs high in its prominent " +
            "position, looking down the rest of the room like some guardian. " +
        "In the center of the room is a large " + LANG_WNUM(COUNCIL_MAX_SIZE) +
            "-sided table dominating the view, with one seat at each of its " +
            "sides. " +
        "You feel that the atmosphere here is one deep contemplation and " +
            "solemn decisions.\n"); 

    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, 1);

    add_item( ({ "banner" }),
        "On the golden, silver-edged banner, are written the words " +
        "\"Fierce in loyalty, dedicated to truth, may justice " + 
        "in Calia never fail\". The words \"help banner\" seem somehow " +
        "to suggest themelves to you.\n");

    add_item( ({ "shields", "shield" }),
        "There are ten shields in all, one for each of the ten " +
        "greatest Calian heroes from the Battle with Kroug, seven " +
        "of whom gave their lives for their cause, leaving Caliana, " +
        "Marrock the Stoic and Krom the Guildmaster as the only " +
        "survivors.\n");

    add_item( ({ "table" }),
        "The table top has " + LANG_WNUM(COUNCIL_MAX_SIZE) + " sides, and is " +
        "made of fine grey marble. In the middle of the table sits the log " +
        "book of the council.\n"); 
  
    add_exit(ROOM("light_boardroom"), "east", 0);
    add_exit(ROOM("light_councilroom2"), "south", 0);
 
    load_book();
    load_board();   

    seteuid(getuid());
    COUNCIL_CODE->load_me();
}


void
info_what_pending(object ob)
{
    if (!objectp(ob))
        return;
   
    ob->command("pending");
}


/*
 * Function:     enter_inv
 * Description:  automatic listing of pending commands
 *               on entry of a council member.  
 */
void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if (interactive(ob) && !ob->query_wiz_level())
        set_alarm(1.0, 0.0, &info_what_pending(ob)); 
}


/*
 * Function:     prevent_enter
 * Description:  Returns 1 if the object is a player who
 *               can enter the council chambers, or a non-
 *               living. Returns 0 otherwise. 
 */ 
int
prevent_enter(object ob)
{
    string nm; 

    if (!living(ob))
        return 0; 

    nm = ob->query_real_name(); 

    if (!(COUNCIL_CODE->is_council_member(capitalize(nm)) ||
          COUNCIL_CODE->is_calian_wiz(ob) || 
          (SECURITY->query_wiz_rank(nm) >= WIZ_ARCH))) 
    {
        tell_object(ob, 
            "You're not coming into the Calian Council " +
            "headquarters without special permission!\n"); 
        return 1; 
    }

    return 0; 
}


int
help(string str)
{
    object tp = TP; 

    if (str != "banner")
        return 0;
    else
    {
        tp->more("_Commands available to council members_\n" +
            "council            - check council members.\n" +
            "pending            - see commands awaiting confirmation.\n" +
            "rempending         - remove your pending commands.\n" +
            "sanctban <player>  - ban <player> from using private rooms.\n" + 
            "trainban <player>  - ban <player> from training.\n" +
            "swarmban <player>  - ban <player> from swarming and mauling.\n" +
            "expel <player>     - expel <player> from the Calian guild.\n" +
            "discharge <player> - discharge <player> from the Calian guild.\n"+
            "rempunish <player> - remove current punishment from <player>.\n" +
            "addreward <player> - add a reward level to <player>.\n" +
            "addmem <player>    - add <player> to the Calian Council.\n" + 
            "remmem <player>    - remove <player> from the Calian Council.\n" +
            "enemies            - check list of enemies of Calia.\n" +
            "addenemy <player>  - add <player> to the list of enemies.\n" +
            "remenemy <player>  - remove <player> from the list of enemies.\n"+
            "addeinfo <player>  - add info about the enemy <player>.\n");            
        return 1;
    }
}


int
see_council(string str)
{
    return COUNCIL_CODE->see_council(str);
}


int
see_pending_commands(string str)
{
    return COUNCIL_CODE->see_pending_commands(str);
}


int
cancel_pending_commands(string str)
{
    return COUNCIL_CODE->cancel_pending_commands(str);
}


int
record_ban_upstairs(string str)
{
    return COUNCIL_CODE->record_ban_upstairs(str);
}


int
record_stop_train(string str)
{
    return COUNCIL_CODE->record_stop_train(str);
}


int
record_stop_swarm(string str)
{
    return COUNCIL_CODE->record_stop_swarm(str);
}


int
record_expel_player(string str)
{
    return COUNCIL_CODE->record_expel_player(str);
}


int
record_discharge_player(string str)
{
    return COUNCIL_CODE->record_discharge_player(str);
}


int
record_remove_punish(string str)
{
    return COUNCIL_CODE->record_remove_punish(str);
}


int
record_add_reward(string str)
{
    return COUNCIL_CODE->record_add_reward(str);
}


int
add_council_member(string str)
{
    return COUNCIL_CODE->add_council_member(str);
}


int
remove_council_member(string str)
{
    return COUNCIL_CODE->remove_council_member(str);
}


int
see_enemies(string str)
{
    return COUNCIL_CODE->see_enemies(str);
}


int
remove_enemy(string str)
{
    return COUNCIL_CODE->remove_enemy(str);
}


int
add_enemy(string str)
{
    return COUNCIL_CODE->add_enemy(str);
}


int
add_enemy_info(string str)
{
    return COUNCIL_CODE->add_enemy_info(str);
}



void 
init()
{
     ::init();
     add_action(help, "help");
     add_action(see_council, "council");
     add_action(see_pending_commands, "pending");
     add_action(cancel_pending_commands, "rempending");
     add_action(record_ban_upstairs, "sanctban");
     add_action(record_stop_train, "trainban");
     add_action(record_stop_swarm, "swarmban");
     add_action(record_expel_player, "expel");
     add_action(record_discharge_player, "discharge");
     add_action(record_remove_punish, "rempunish");
     add_action(record_add_reward, "addreward");
     add_action(add_council_member, "addmem");
     add_action(remove_council_member, "remmem");
     add_action(see_enemies, "enemies");
     add_action(remove_enemy, "remenemy");
     add_action(add_enemy, "addenemy");
     add_action(add_enemy_info, "addeinfo"); 
}

