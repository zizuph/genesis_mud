/*
 * This object may be used to offer an egg to all players in the game for
 * Easter.  Taken from Mercade's Beer giver, stolen pretty much lock,
 * stock and barrel by Dunstable. Enhanced by zima!
 */
 
inherit "/std/object";
 
#define NF(x) notify_fail(x)
#define TO this_object()
#define ENV(x) environment(x)
#define TP this_player()
#define CAP(x) capitalize(x)
#define BSN(x) break_string(x,75) + "\n"
#define EGG "/d/Shire/private/old_wiz/dunstable/open/egg"
 
 
void
create_object()
{
    set_name("tool");
    add_adj("easter");
    set_short("celebration tool");
    set_long(BSN("You can give everyone in the game an egg with the command " +
        "<eggall> or <eggneedy> for all who don't have an egg, "+
        "or <eggplayer 'name'> for an individual. "+
        "Don't be stingy with the eggs, now!"));
}
 
void give_egg(object player) {
   object egg = clone_object(EGG);
   player->catch_msg(BSN("A fuzzy bunny rabbit hops up next to you. " +
       "The bunny wrinkles her nose a bit before holding out a basket "+
        "full of brightly-colored eggs.\n"));
       player->catch_msg("The bunny rabbit offers you an egg.\n");
   if(egg->move(player))
   {
       player->catch_msg("For some reason you aren't able to accept " +
           "it though.\n");
       write(player->query_name() + " didn't get an egg.\n");
   }
   else
   {
       player->catch_msg("You happily accept the offered egg.\n");
       write(player->query_name() + " took an egg.\n");
   }
}
 
int
do_egg(string cmd)
{
    object *players;
    object egg;
    int i, needyonly=(cmd=="needy");
 
 
    players = users();
    setuid();
    seteuid(getuid(TO));
 
    for (i = 0; i < sizeof(players); i ++)
       if ((!needyonly) || (!present("easter egg",players[i])))
          give_egg(players[i]);
 
    return 1;
}
 
int do_eggall() { do_egg("all"); return 1; }
int do_eggneedy() { do_egg("needy"); return 1; }
int do_eggplayer(string cmd)
{
   object player=find_player(lower_case(cmd));
   if (!objectp(player))
      write("The bunny couldn't find "+cmd+"!\n");
   else
      give_egg(player);
   return 1;
}
 
void
init()
{
    ::init();
 
    if (TP->query_wiz_level())
    {
        add_action(&do_eggall(),   "eggall");
        add_action(&do_eggneedy(), "eggneedy");
        add_action(&do_eggplayer(),  "eggplayer");
    }
 
    return;
}
 
