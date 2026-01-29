
inherit "/std/object";


int gFee = 150;
string gExit1 = "east";
string gExit2 = "west";
string gRoom1 = "";
string gRoom2 = "";
object gGuard = 0;


void
set_fee(int fee)
{
    gFee = fee;
}

void
update_rooms()
{
    mixed *exits = E(TO)->query_exit();
    int i;
    
    for(i=1;i<sizeof(exits);i+=3)
    {
	if (exits[i] == gExit1)
	  gRoom1 = exits[i-1];
	else if (exits[i] == gExit2)
	  gRoom2 = exits[i-2];
    }
}

void
set_exits(string exit1, string exit2)
{
    gExit1 = exit1;
    gExit2 = exit2;

    update_rooms();
}

void
create_object()
{
    set_short("closed turnpike");
    set_long("This is a standard turnpike which is closed and which is " +
	     "blocking your way.\n");
    
    (gGuard = clone_object(gGuardPath))->move(E(TO),1);
}

int
block_player()
{
    int maynotpass = 0;

    if (gGuard && E(gGuard) == E(TO))
      maynotpass = 1;
    /* if player belongs to occupying army, let him/her pass */
    if (E(TO)->query_area_name() && ARMYMASTER->army_in_area(E(TO)->query_area_name()) &&
	ARMYMASTER->army_of_player(TP) == ARMYMASTER->army_in_area(E(TO)->query_area_name()))
      maynotpass = 0;
    /* if player has bribed his/her way thru, let him/her pass */
    if (0)
      maynotpass = 0;
    /* if player is a newbie, let him/her pass */
    if (TP->query_average_stat() < 30)
      maynotpass = 0;
    /* add more pass options here */

    if (maynotpass)
      gGuard->command("say You are not allowed to pass, " + TP->query_nonmet_name() + ".\n");
    else
    {
	gGuard->command("say At your service, " + TP->query_nonmet_name() + ".\n");
	tell_room(E(TO),"The turnpike rises briefly to let " + QTNAME(TP) + " pass.\n",({TP}));
	tell_object(TP,"The turnpike rises briefly to let you pass.\n");
    }
    return maynotpass;
}

int
do_anything(string str)
{
    string verb = query_verb();
    string prevroom = file_name(TP->query_prop(LIVE_O_LAST_ROOM));

    if ((verb == gExit1 && prevroom == gRoom2) ||
	(verb == gExit2 && prevroom == gRoom1))
      return block_player();
    else
      return 0;
}

void
enter_env(object dest, object old)
{
    ::enter_env(dest, old);
    set_alarm(0.0,0.0,update_rooms);
}

void
init()
{
    add_action(do_anything, "", 1);
    ::init();
}
