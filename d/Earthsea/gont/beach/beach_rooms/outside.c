/*
* Outside the fisherman hut , created by Ged 6/10/2001
*/

#include "default.h"

inherit SANDY;

object fisherman,boat;

void i_am_the_fisherman(object f) 
 {
  fisherman=f;
  boat->i_am_the_fisherman(f);
 }

void create_beach()
{
 set_short("Small pier");
 set_long("You are standing on the small pier , running straight into "+
   "the open sea. Near the pier you see small hut , some fishermen "+
   "apparently live here.\n");

 add_exit(BEACH_DIR+"hut","hut");
 add_exit(BEACH_DIR+"beach12","north");

 setuid();
 seteuid(getuid());

 boat=clone_object(BEACH+"obj/boat");
 boat->move(TO);
}

void whisper(object who)
{
 fisherman->command("whisper to "+who->query_real_name()+" Just enter "+
   "the boat when you ready...");
}

void enter_inv(object who,object from)
{
 if(!fisherman) return;
 if(ENV(fisherman)!=TO) return;
 if(!who->query_prop("_live_i_asked_fisheman")) return;

 set_alarm(0.5,0.0,&whisper(who));
}

void notify_board_boat(object who)
{
 if(who==fisherman) return;

 fisherman->go_boat();
}

void remove_boat() {boat->move(find_object(OPEN_SEA));}

