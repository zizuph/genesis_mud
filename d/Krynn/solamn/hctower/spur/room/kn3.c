// kn4.c   High Warrior Room
// grace sept 1994

#include "../local.h"
#include <stdproperties.h>

inherit SPURRM;

#undef ADMIN
#define ADMIN     "/d/Krynn/guilds/knights/admin/admin"
#undef CONCLAVE_OBJ
#define CONCLAVE_OBJ "/d/Krynn/guilds/knights/obj/conclave_cmd"
#define CONCLAVE_OB_ID "knight_conclave_command_object"
#define MAILREADER_ID   "_reader_"
#define CROWN     ADMIN->query_conclave("crown")
#define WAIT \
   ({  \
      ROOM + "kn1", \
      ROOM + "void", \
   })


void
create_spur_room()
{

   SHORT("High Warrior Room");
   LONG("This is the private "+
     "office of "+ CROWN + ", the High Warrior of the Solamnian Knights."+
     "  The main body of the room is empty space, though a stalwart "+
     "desk and chair stand vigilant.  A fireplace adorns the south wall,"+
     " with the massive, tusked head of an albino boar mounted above "+
     "it.  A small library is set into the northwest corner, its varied cont"+
     "ents spared from damp-rot by the heat of the fire.  Three brilliant "+
     "tapestries adorn stone walls the colour of grey thunderclouds.  A "+
     "well-used cushion occupies a small corner of the floor, and across "+
     "from it is a small window cut into the wall near the door.\n");

   INSIDE;
   LIGHT;
 
   clone_object(SOBJ + "crown_b")->move(TO);

   AI(({"fire","fireplace","firewood","woodbox", "tongs", "tools"}),
       "The fireplace itself is purely functional, though a small replica "+
       "Dragonlance adorns the mantle. The warmth radiating from the"+
       " fireplace is comforting and relaxing.\n");
   AI(({"boar", "head", "boars head"}),
       "This boar's head wears an extremely disgruntled expression.  "+
       "The dingy condition of its once-white fur indicates that it has "+
       "been settled above the mantle for quite some time.  You sus"+
       "pect that this trophy was the result of some long-ago Autumn "+
       "Hunt, an activity the Knights of Solamnia sometimes partake in.\n");
   AI(({"tapestry", "tapestries"}),
       "The first tapestry to catch your eye is one featuring Huma tot"+
       "ing a Dragonlance, heroically facing the five-headed dragon "+
       "avatar of Takhisis.\n"+
        "The second depicts a portrait of Vinas Solamnus, as he " +
        "stands courageously against the injustices inflicted upon " +
        "the people of Solamnia.\n"+
       "The third tapestry is epic in proportion, a scene from a seem"+
       "ingly hopeless battle against terrible odds: A large group of "+
       "loyal Crown Knights obediently following their High Warrior, "+
       "valiantly cutting their way through a DragonArmy horde in "+
       "the face of almost certain death.\n");
   AI(({"desk", "chair"}),
       "Made of vallenwood, a tree found only in the forests near So"+
       "lace, the desk supports the weight of the High Warrior's cor"+
       "respondence and journals, while the chair occasionally sup"+
       "ports this Knight's weight when time can be found to sit down.\n");
   AI(({"scrolls", "parchments"}),
       "The large amount of paperwork which dominates this desk attest"+
       "s to the workload of a High Knight.  You see mails from Knights "+
       "and non-Knights, commissions of supplies, and sketched battle"+
       "plans.\n");
   AI(({"library","bookcase"}),
       "A modest personal collection of aging books.\nMost of the titles "+
       "are illegible, blurred from years of handling. One entire shelf is "+
       "dedicated to the 37 volumes of the Measure, while another con"+
       "tains such titles as: 'The History of the Solamnic Knights', 'Gilthan"+
       "as' Notes on Dragonriding', 'The Legend of Huma', and 'The Ham"+
       "mer of Kharas'.\n");
    AI(({"cushion", "pillow"}),
       "This soft purple pillow bears twin indentations, indicative of fre"+
       "quent use. The stone floor before it is heavily worn, marked with"+
       " scratches and nicks from frequent contact with metal armours.\n"+
       "It would appear that someone kneels here quite often.\n");
    AI("window", "This window provides a view of the waiting room.\n"+
        "To see into it, try to <view room>.\n");
 
}

// This won't work on kn1.c due to the changes in the player's
// short descriptions when they sit on the chairs.
string
wait_desc()
{
  string *roomfiles;
  object *inv, *live, room;
  int i;

  roomfiles = WAIT;
  inv = ({});
  for (i = 0; i < sizeof(roomfiles); i++)
    {
    if ((room = find_object(roomfiles[i])) != 0)
      inv += all_inventory(room);
    }

  if (inv && sizeof(inv) > 0)
    {
    live = FILTER_LIVE(inv);
    if (sizeof(live) > 0)
      return ("In that room you can see " +
              COMPOSITE_LIVE(live) + ".\n");
    }
    return ("At present, the room appears to be empty.\n");
}
                                                                                                                                                    
                                                                 
init()
{
   add_action("do_view", "view");
   set_alarm(0.1,0.0,"do_write_welcome",TP);
}

int                                                                           
do_view(string str)
{                                                                             
     object old_env;   

     old_env = environment(this_interactive());
                                                                                                
     if (!str || str == "room" || str =="waiting room")
     {
     write("=================================================="+
              "====================\n");
     this_interactive()->move(ROOM + "kn1.c");
     this_interactive()->command("l");                                        
     this_interactive()->move(old_env);                                       
     write("=================================================="+
             "====================\n");
     return 1;
     }
   return 0;
}                                                                             
                                                                              


void
do_write_welcome(object who)
{
    object mr;
    string ro = (ADMIN)->query_conclave("rose"),
           sw = (ADMIN)->query_conclave("sword"),
           cr = (ADMIN)->query_conclave("crown");
    string *conclave = ({ });

    int a = (ADMIN)->check_can_perform_command(who);
    object p = P(CONCLAVE_OBJ, who);
    mixed c = !p;

    if (c && a)
      {
	  who->catch_msg("In this room you have access to the conclave " +
			 "command object. Examine it to see your commands. " +
			 "If you have problems, suggestions or " +
			 "improvements, contact Aridor.\n");
	  clone_object(CONCLAVE_CMD)->move(who,1);

	  if (ro && stringp(ro) && ro != "")
	    conclave += ({ ro });
	  if (sw && stringp(sw) && sw != "")
	    conclave += ({ sw });
	  if (cr && stringp(cr) && cr != "")
	    conclave += ({ cr });
	  ::init();
	  mr = clone_object("/secure/mail_reader");
	  if (conclave)
	    mr->set_alias("conclave", conclave);
	  if (GUILDMASTERS)
	    mr->set_alias("guildmaster", GUILDMASTERS);
	  mr->move(who, 1);
      }
}

void
leave_inv(object ob, object to)
{
    object reader;
    ::leave_inv(ob, to);
    
    reader = present(MAILREADER_ID, ob);
    if (reader)
      reader->remove_object();

    reader = present(CONCLAVE_OB_ID, ob);
    if (reader)
        reader->remove_object();
}
