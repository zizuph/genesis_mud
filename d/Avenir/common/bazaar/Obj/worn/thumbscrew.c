/* created by Grace  29 May 1994  */
/* a joke with Ged as the butt :) */

inherit "/std/armour";
#include "/d/Avenir/common/bazaar/bazaar.h"
#include "/sys/wa_types.h"

void
create_armour()
{
   set_short("wooden thumbscrew");
   set_pshort("wooden thumbscrews");
   set_name("thumbscrew");
   add_name(({"thumbscrew", "screw", "thumbscrews"}));
   add_adj("wooden");
   set_at(A_HANDS);         
   add_prop(OBJ_I_WEIGHT, 250);  	/* 0.25 kg */
   add_prop(OBJ_I_VOLUME, 500);         /* 0.5  L  */    
   add_prop(OBJ_I_VALUE,  70);
   
   set_long("This is one of the torture devices used in Sybarus dungeons.\n" +
     "A thumbscrew is an instrument which fits over both thumbs. It has two " +
     "screws with flat heads that may be turned to compress the thumbs. " +
     "The pressure applied can be excruciating, prompting the unfortunate " +
     "wearer to say or do anything to relieve the pain.\n");
   add_item(({"head", "heads"}), 
     "Turning the flat heads of the screws will apply pressure to thumbs.\n");
   add_cmd_item("thumbscrew", "help", "Turning the screws when "+
      "the thumbscrew is worn can cause excruciating pain.\n");
}

void
init()
{
   ::init();
   add_action("t_func", "turn");
}

int
t_func(string arg)
{
    if (!arg)
    {
        notify_fail("Do what with the thumbscrew?\n");
        return 0;
    }
    if (arg == "screw" || arg == "head" || arg == "heads" || 
        arg == "thumbscrew")
    {
        if (!query_worn())
        {
            write("You turn the head of the thumbscrew.\nIt would "+
                "probably be more interesting if someone was wearing "+
                "it when the heads of the thumbscrew are turned.\n");
            return 1;
        }
        TP->catch_msg("The pressure on your thumbs increases.\n" +
            "You feel an terrible pain running up your arms from "+
            "your thumbs.\nA scream builds up inside your mind, " +
	    "but you refuse to give it voice.\n"); 
        say(QCTNAME(TP) +" begins to turn something on the "+
 	    "thumbscrew.\n"+ QCTNAME(TP) +" is suddenly quite still, "+
            TP->query_possessive() +" body frozen in an attitude of "+
            "extreme pain.\n");
        TP->command("remove thumbscrew");
        return 1;
    }
    write("Do what with the thumbscrew?\n");
    return 1;
 }


