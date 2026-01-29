/*
 *  /d/Gondor/open/sps.c
 *
 *  This file contains the game scissors, paper, stone. If you want to
 *  teach your NPC play this game, just inherit this file and initiate
 *  the game in init_living(). Following steps will do the job:
 *
 *  inherit "/d/Gondor/open/sps";
 *
 *  void
 *  init_living()
 *  {
 *      ::init_living();
 *
 *      init_sps_game();
 *  }
 *
 *  Deagol, March 2003
 */

#pragma save_binary
#pragma strict_types

inherit "/lib/commands";

#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>

/*
 *  Global variables
 */
object	npc = this_object();
object	player = this_player();
string	player_name;
int	busy_flag;

/*
 *  Prototypes
 */
void	draw_message();
void	lose_message();
void	win_message();
void	sps_hook_draw();
void	sps_hook_lose();
void	sps_hook_win();
void	init_sps_game();
int	play_sps_game(string str);
string	npc_shows;
string	player_shows;

/*
 *  Function name: init_sps_game
 *  Description  : This function adds the play command to a NPC that inherits
 *                 this object
 */
void
init_sps_game()
{
    add_action(play_sps_game, "play");
}

void
set_busy_flag()
{
    busy_flag = 1;
}

void
unset_busy_flag()
{
    busy_flag = 0;
}

void
sps_hook_draw()
{
    npc->command("say to " + player_name + " Wow, it's a draw! Let's " +
        "try your luck again.");
}

void
sps_hook_lose()
{
    npc->command("say to " + player_name + " I'm the best!");
}

void
sps_hook_win()
{
    npc->command("say to " + player_name + " You win! The next time " +
        "I'll beat you.");
}

/*
 *  Function name: draw_message
 *  Description  : This function is called in init_sps_game() when it's
 *                 a draw.
 */
void
draw_message()
{
    set_alarm(0.2, 0.0, &npc->command("say ONE!"));
    set_alarm(1.0, 0.0, &npc->command("say TWO!"));
    set_alarm(1.8, 0.0, &npc->command("say THREE!"));
    set_alarm(1.9, 0.0, &write(npc->query_The_name(this_player()) +
        " holds " + npc->query_possessive() + " " + npc_shows + ".\n"));
    set_alarm(1.9, 0.0, &say(QCTNAME(npc) + " holds " +
        npc->query_possessive() + " " + npc_shows + ".\n"));
    set_alarm(2.0, 0.0, &write("You hold your " + player_shows + ".\n"));
    set_alarm(2.0, 0.0, &say(QCTNAME(player) + " holds " +
        player->query_possessive() + " " + player_shows + ".\n"));
    set_alarm(2.3, 0.0, &sps_hook_draw());
    set_alarm(2.3, 0.0, &unset_busy_flag());
}

/*
 *  Function name: lose_message
 *  Description  : This function is called in init_sps_game() when a player
 *                 lose.
 */
void
lose_message()
{
    set_alarm(0.2, 0.0, &npc->command("say ONE!"));
    set_alarm(1.0, 0.0, &npc->command("say TWO!"));
    set_alarm(1.8, 0.0, &npc->command("say THREE!"));
    set_alarm(1.9, 0.0, &write(npc->query_The_name(this_player()) +
        " holds " + npc->query_possessive() + " " + npc_shows + ".\n"));
    set_alarm(1.9, 0.0, &say(QCTNAME(npc) + " holds " +
        npc->query_possessive() + " " + npc_shows + ".\n"));
    set_alarm(2.0, 0.0, &write("You hold your " + player_shows + ".\n"));
    set_alarm(2.0, 0.0, &say(QCTNAME(player) + " holds " +
        player->query_possessive() + " " + player_shows + ".\n"));
    set_alarm(2.3, 0.0, &npc->command("grin misc " + player_name));
    set_alarm(2.4, 0.0, &sps_hook_lose());
    set_alarm(2.4, 0.0, &unset_busy_flag());
}

/*
 *  Function name: win_message
 *  Description  : This function is called in init_sps_game() when a player
 *                 wins.
 */
void
win_message()
{
    set_alarm(0.2, 0.0, &npc->command("say ONE!"));
    set_alarm(1.0, 0.0, &npc->command("say TWO!"));
    set_alarm(1.8, 0.0, &npc->command("say THREE!"));
    set_alarm(1.9, 0.0, &write(npc->query_The_name(this_player()) +
        " holds " + npc->query_possessive() + " " + npc_shows + ".\n"));
    set_alarm(1.9, 0.0, &say(QCTNAME(npc) + " holds " +
        npc->query_possessive() + " " + npc_shows + ".\n"));
    set_alarm(2.0, 0.0, &write("You hold your " + player_shows + ".\n"));
    set_alarm(2.0, 0.0, &say(QCTNAME(player) + " holds " +
        player->query_possessive() + " " + player_shows + ".\n"));
    set_alarm(2.2, 0.0, &npc->command("gasp"));
    set_alarm(2.4, 0.0, &sps_hook_win());
    set_alarm(2.5, 0.0, &npc->command("congrat " + player_name));
    set_alarm(2.5, 0.0, &unset_busy_flag());
}

/*
 *  Function name: play_sps_game
 *  Description  : The main function that initiate the SPS game.
 *  Arguments    : string str - player's move (scissors, paper or stone)
 *  Returns      : 0 or 1
 */
int
play_sps_game(string str)
{
    int		npc_move;
    int		player_move;

    if (!strlen(str) || !parse_command(str, ({}),
        "'game' 'scissors' / 'paper' / 'stone' / 'rock'"))
    {
        notify_fail("Play what?\n", 0);
        return 0;
    }

    npc = this_object();
    player = this_player();
    player_name = player->query_real_name();

    if (busy_flag)
    {
        npc->command("say to " + player_name + " I'm busy, are you blind?");
        return 1;
    }

    npc_move = random(3);
    set_busy_flag();

    switch(npc_move)
    {
        case 0 :		/* scissors */
            npc_shows = "hand with two fingers extended in a V shape";
            break;
        case 1 :		/* paper */
            npc_shows = "hand flat";
            break;
        case 2 :		/* stone */
            npc_shows = "fist clenched";
            break;
        default :
            npc_shows = "nothing";
            break;
    }

    switch(str)
    {
        case "game scissors" :
            player_move = 0;
            player_shows = "hand with two fingers extended in a V shape";
            break;
        case "game paper" :
            player_move = 1;
            player_shows = "hand flat";
            break;
        case "game stone" :
            player_move = 2;
            player_shows = "fist clenched";
            break;
        case "game rock" :
            player_move = 2;
            player_shows = "fist clenched";
            break;
        default :
            player_move = -1;
            break;
    }

    if (npc_move == player_move)
    {
        draw_message();
        return 1;
    }
    
    if (npc_move == 0 && player_move == 1)
    {
        lose_message();
        return 1;
    }

    if (npc_move == 0 && player_move == 2)
    {
        win_message();
        return 1;
    }

    if (npc_move == 1 && player_move == 0)
    {
        win_message();
        return 1;
    }
    
    if (npc_move == 1 && player_move == 2)
    {
        lose_message();
        return 1;
    }

    if (npc_move == 2 && player_move == 0)
    {
        lose_message();
        return 1;
    }

    if (npc_move == 2 && player_move == 1)
    {
        win_message();
        return 1;
    }

    write("npc:    " + npc_move + "\n");
    write("player: " + player_move + "\n");
    write("Eeeks!\n");
    return 1;
}
