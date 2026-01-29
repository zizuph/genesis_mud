/* meditate.c: Gladiator meditation room: Serpine, 4-24-95 */
 
#pragma save_binary
#pragma strict_types
 
inherit "/lib/guild_support";
inherit "/d/Cirath/std/room";
#include "defs.h"
#define CHARGE_LOG (PSION_LOG+"chargeob.log")
#define CHARGE_ALLOW (PSION_LOG+"chargeok.txt")
 
object meditate;
 
void create_room()
{
    set_short("silent room");
    set_long("This chamber is empty save for the pads covering the entire "+
             "floor. Within this room gladiators can 'workout' to focus their "+
             "rage and anger into the sheer destructive power they are "+
             "known for. A few can 'setcharge' here as well.\n");
 
    add_item(({"pad", "pads"}), "The pads serve to protect the meditating "+
             "gladiator, wether they choose to do so via contemplation or "+
             "martial arts exercises.\n");
 
   INSIDE
 
   add_exit(PSION_ROOM + "gldboard.c", "west", 0, 1);
}
 
int
query_no_snoop()
{
   return 1;
}
 
void
gs_hook_start_meditate()
{
    write("" +
        "You begin with some simple stretches, then begin to work in "+
        "some martial arts kicks and jabs. Soon you are in the midst of "+
        "an intense workout involving simulated weapon moves. Your mind "+
        "and body, pushed to the limit, scream in unison until in a "+
        "flash of pain they are one.\nYou find yourself able to "+
        "<set> your different preferences as you wish. Just <rise> "+
		"when you are finished.\n");
    say(QCTNAME(this_player()) + " enters into a martial trance through "+
        "the use of a series of combat moves.\n");
}
 
void
gs_hook_rise()
{
    write("Gradually you lessen the intensity of the workout. Soon you "+
          "feel mind and body resuming their normal relationship.\n");
    say(QCTNAME(this_player()) + " relaxes the workout and returns "+
          "to a normal state of mind.\n");
}
 
int
allowedchstr(string subject)
{
    int zip = 1;
    string current_line;
    string testcharge;
 
    testcharge=extract(subject+"                                    ",0,30);
 
    while(current_line=read_file(CHARGE_ALLOW,zip,1))
    {
        if (testcharge==extract(current_line,0,30))
            return 1;
        if (extract(current_line,0,3)=="END") return 0;
        if (zip>250) return 0;
        zip=zip+1;
    }
    return 0;
}
 
int
setcharge (string str)
{
    object PSION = TP;
    object chargeob = present("_glad_charge_ob_", PSION);
 
    if (!strlen(str))
    {
        NF("Use 'setcharge <text>'.\n");
        return 0;
    }
 
    if ((PSION->query_psionict_level()) < CHARGE_OB_LEVEL)
    {
        NF("You don't feel seasoned enough to do such a thing.\n");
        return 0;
    }
 
    if (strlen(str)>30)
    {
        NF("Description can only be up to 30 characters.\n");
        return 0;
    }
    if (!allowedchstr(str))
    {
        NF("That is not a valid special attack.\n"
          +"  Try 'help gladiator chargeok'.\n");
        return 0;
    } 
 
 
    if (!chargeob) ((chargeob = CO(PSION_OBJ+"chargeob"))->move(PSION));
    chargeob->set_charge_desc(str);
    WRITE_LOG(CHARGE_LOG, PSION, ": "+str);
 
    PSION->catch_msg("Custom charge string set!\n"+
      "An example of how it will appear in combat is:\n"+
      " 'You strike a gith with your "+str+".'\n"+
      "Also be aware of the rules in 'help gladiator setcharge'.\n");
    return 1;
}
 
void init()
{
   ::init();
   init_guild_support();
   add_action("gs_meditate", "workout");
   add_action("setcharge", "setcharge");
}
