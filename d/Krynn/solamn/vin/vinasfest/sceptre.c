/* trumpet for blowing */

inherit "/std/object";

#include "/d/Raumdor/open/special/vfest/vfest.c"

#define C(xxx)       capitalize(xxx)
#define FEATHER	     "/d/Krynn/solamn/vin/vinasfest/feather"
#define	AWARDED	     "_live_i_awarded"

void
create_object()
{
	set_name("sceptre");
	set_short("golden sceptre");
	set_long("The sceptre is made of purest gold. "+
	         "It's head is dorned with 4 large rubies. Around the hilt, "+
		 "dark-red silk cord is wrapped. Clearly this is more " +
		 "ceremonial object then weapon.\nIn small runes, "+
		 "just belowe head of the sceptre, someone "+
		 "wrote 'help sceptre'.\n");
	add_prop(OBJ_I_NO_DROP,1);
        add_prop(OBJ_I_NO_STEAL,1);
	add_prop(OBJ_I_NO_SELL,1);
	add_prop(OBJ_I_NO_BUY,1);
	add_prop(OBJ_I_NO_DROP,1);
	seteuid(getuid(this_object()));	

}

void
init()
{
	add_action("help_sceptre", "help");
	add_action("vinvite", "vinvite");
	add_action("vreturn", "vreturn");
	add_action("vaward", "vaward");
	add_action("vdiscard", "vdiscard");
}

int
help_sceptre(string str)
{
	notify_fail("Help what?\n");
	if (!str)
	return 0;
	
	if (str == "sceptre")
	write("This sceptre is designed for you to control what happens " +
	    "during the Vinasfest. The commands are:\n" +
	    " <vinvite someone> - you will send invitation to player,\n" +
	    " <vreturn someone> - if you decide you do not want someone\n" +
	    "                    to be on the Vinasfest,\n"+
	    " <vaward someone> - this command will award winner of jousting,\n"+
	    " <vdiscard sceptre> - if you do not want to have it with you.\n"+
	    "\n");
       return 1;
}

int
vinvite(string whom)
{
    object player;

    notify_fail("Vinvite whom?\n");
    if (!whom)
     return 0;
    
    write("You grip the sceptre and concentrate.\n");
    do_invite(whom);
    return 1;
}

int
vreturn(string whom)
{
    object player, invitation;

    notify_fail("Vreturn whom?\n");
    if (!whom)
     return 0;

    player=find_player(whom);
    
    if (player->query_prop(LIVE_O_ROOM_BEFORE_VFEST))
    {
      write("You force " + player->query_name() + " to leave Vinasfest.\n"); 
      player->command("$return me");
    }
 
    return 1;
}

int
vaward(string whom)
{
    object award, player;

    notify_fail("Vaward whom?\n");
    if (!whom)
     return 0;
 
    award = clone_object(FEATHER);
    player = find_player(whom);

    notify_fail("There is no such player in game.\n");
    if (!player)
      return 0;

    notify_fail("The player is _NOT_ a knight!\n");
    if (!player->query_knight_level())
      return 0;

    if (this_object()->query_prop(AWARDED))
	write("You have already given award away!\n");

    write("You becone at " + QNAME(player) + ". " + C(HE(player)) + 
          "advances to you and kneels down.\n");
    write("You give small golden feather to " + QNAME(player) + ".\n");
    say(QCTNAME(TP) + " becones at " + QNAME(player) + ". The knight " + 
          "advances and kneels down infront of " + QCNAME(TP) + ".\n");
    say(QCTNAME(TP) + " gives small golden feather to " + QNAME(player) + ".\n");
    award->move(player,1); 
    this_object()->add_property(AWARDED);

    return 1;
}

int
vdiscard(string what)
{
    notify_fail("Vdiscard sceptre maybe?\n");
    if (!what)
     return 0;
     
    if (what == "sceptre")
    {
     write("You break the sceptre and as you do that it turns into dust!\n");
     remove_object();
     return 1;
    }
    
    return 0;
}
