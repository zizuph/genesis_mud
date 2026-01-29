/*
 * The guild object for School of High Magic
 */

#pragma save_binary
#pragma strict_types

inherit "/std/object";
inherit "/lib/keep";

#include <stdproperties.h>
#include <macros.h>
#include <cmdparse.h>
#include <filter_funs.h>
#include <files.h>
#include <ss_types.h>
#include "/d/Krynn/guilds/sohm/defs.h"
#include "spellbook_spells.h"

// Prototypes
public void             create_object();

public void
create_object()
{
    set_name("spellbook");
    add_adj(({"leather-bound","leather","bound"}));
    add_name("sohm_guild_object");
    set_short("leather-bound spellbook");
    set_long("This leather-bound tome is the closely-guarded repository of "+
          "spells for a student of the School of High Magic. You can list " +
          "spells collected by reading it. Information about the School of " +
          "High Magic can also be found within, which can be accessed " +
          "through the <help sohm> command.\n");

    add_prop(OBJ_M_NO_INS, 1); 
    add_prop(OBJ_I_NO_DROP,1);
    add_prop(OBJ_M_NO_SELL,1);
    add_prop(OBJ_I_NO_GIVE,1);
    add_prop(OBJ_I_WEIGHT, 40);
    add_prop(OBJ_I_VOLUME, 254);
    add_prop(OBJ_I_VALUE, 678);;
    add_prop(OBJ_M_NO_STEAL,1);

    // add_cmd_item(({"leather-bound spellbook","spellbook"}),"read","@@read_cmd");

}

int
do_spellbook(string str)
{
    object spellbook;
    string arg, guild_str;    

    if(!str)
    {
        notify_fail("Read what?\n");
        return 0;
    }

    if ((!parse_command(str, this_player(), "%o", spellbook) &&
        !parse_command(str, this_player(), "%o %s", spellbook, arg)))
    {
        notify_fail("Read what?\n");
        return 0;
    }

    if (spellbook != this_object())
    {
        notify_fail("Read what?\n");
        return 0;
    }

    if(this_player()->query_guild_name_occ() != "School of High Magic" &&
       this_player()->query_guild_name_occ() != "Wizards of High Sorcery") 
    {
        notify_fail("You are unable to decypher the magical runes " +
        "within the spellbook.\n");
        return 0;
    }  

    if(this_player()->query_guild_name_occ() == "School of High Magic")
      guild_str = "sohm";
    else 
      guild_str = "wohs";

    if(arg)
    {
      if(arg != "cantrip spells" && arg != "minor spells" && arg != "lesser spells" &&
         arg != "greater spells" && arg != "advanced spells")
      {
          write("Read what in the spellbook? Your cantrip spells? " +
             "Minor spells? Lesser spells? Greater spells? Advanced spells?\n");
          return 1;
      }
    }

    say(QCTNAME(this_player()) + " opens " +this_player()->query_possessive()+ 
          " spellbook and begins studying the mystical runes within.\n");     
    write("You open your spellbook and examine the spells you have recorded within.\n");

    msg = "\n\n\t                     ~~**~~  Scribed Spells  ~~**~~                    \n"+
"\t     _____________________________   ______________________________ \n"+
"\t .-/|            ~~**~~           \\ /              ~~**~~          |\\-. \n"+
"\t ||||                              :                               |||| \n"+
"\t ||||   Spell:                     :    Description:               |||| \n"+
"\t ||||                              :                               |||| \n";

    if(!arg)
    {
       sohm_cantrip_spells();
       sohm_minor_spells();
       sohm_lesser_spells();
       sohm_greater_spells();
       sohm_advanced_spells();
    }
    else if(arg == "cantrip spells")
       sohm_cantrip_spells();
    else if(arg == "minor spells")
       sohm_minor_spells();
    else if(arg == "lesser spells")
       sohm_lesser_spells();
    else if(arg == "greater spells")
       sohm_greater_spells();
    else if(arg == "advanced spells")
       sohm_advanced_spells();
    
    msg +=
"\t ||||                              :                               |||| \n"+
"\t ||||                              :                               |||| \n"+
"\t ||||_____________________________ : ______________________________|||| \n"+
"\t |||/=============================\\:/==============================\\||| \n"+
"\t `-------------------------------~___~--------------------------------' \n\n" +
"\t     For details about each scribed spell check help " +guild_str+ " <spell>.       \n\n"+
"\t     Spells memorised are listed in this spellbook with an *.            \n"+
"\t     For a list of memorised spells use the 'spells' command.            \n";

    write( msg );    

    return 1;
}
       

void
init()
{
    ::init();

    add_action(do_spellbook, "read");
}

