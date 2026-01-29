// Knight training room #3: clerical skills
// grace
// Feb 1995
// code modelled after train1.c at Vkeep

inherit "/lib/skill_raise";

#include "../local.h"
#include <ss_types.h>

inherit SPURRM;
inherit "/d/Krynn/open/room_tell";

#define CLOSED          0       /* 1 = closed,   0 = open.  */
#define SS_MAGIC_ELEMENTS ({SS_ELEMENT_LIFE })
#define SS_MAGIC_FORMS    ({ SS_FORM_ENCHANTMENT, \
                                          SS_FORM_DIVINATION })

object trainer;

/*
 * Prototypes
 */
void set_up_skills();
void reset_spur_room();

int closed = 0;

void
create_spur_room()
{
    closed = CLOSED;

    SHORT("Clerical training room");
    LONG("   The walls "+
        "of this large hall are draped in whitest wool from the ceil"+
        "ing to the polished marble floor. Here and there a break in "+
        "the draperies reveals cabinets and shelves built into the "+
        "walls.  Stone columns provide support for the "+
        "domed ceiling, as well as hooks from which numerous lamps "+
        "hang, radiating heat and light.  Rows of tables form con"+
        "centric circles around the room's center, which is occupied "+
     "by a simple podium.  Scattered on the tables are various "+
     "tomes and scrolls over which Sword and Rose Knights pursue "+
     "their clerical studies.  A small placard rests on the podium.\n");


    add_item(({"ceiling", "dome", "domed ceiling", "constellation", 
		 "sky", "moon", "solinarri"}),
	     "The ceiling is a large circular dome which "+ 
	     "has been constructed to resemble the sky "+        
	     "at night. Your eyes pick out several familiar "+ 
	     "constellations and the white moon called "+         
	     "Solinari.\n");
    
    add_item(({"walls", "wall"}),                               
	     "The walls are made of the same dark stone as "+
	     "the rest of the Knights' Spur. They are draped "+
	     "with white woolen cloth and have shelves and "+     
	     "cabinets built into them at regular intervals.\n");  
    
    add_item(("light"), 
	     "The light in the room is bright, but no so much that "+
	     "it hurts the eyes. Rather, it is perfect for reading. "+ 
	     "It comes from the many brass lanterns hanging from "+ 
	     "both ceiling and columns, but is reflected from the "+ 
	     "draperies, columns, and floor in such a way that the"+ 
	     "entire room seems aglow.\n");
    
    add_item(({"lamp", "lamps", "lantern", "lanterns"}), 
	     "The large brass lamps suffuse the area with a bright "+ 
	     "white glow. They are of antique construction, and seem "+ 
	     "quite valuable.\n");
    
    add_item(({"draperies", "wool", "curtain", "curtains"}), 
	     "The draperies loosely hang down from the ceiling to the "+ 
	     "floor, and gently sway as you move through the room. "+ 
	     "They are of soft wool, and perfectly white. They seem to "+ 
	     "absorb sounds in the room, creating an atmosphere of "+ 
	     "peaceful silence.\n");
    
    add_item(({"columns", "column", "cornice", "hook", "bracket"}), 
	     "The columns are smooth and white. They form a large "+ 
	     "circle which supports the dome overhead.  From the "+ 
	     "cornice of each column project brackets from which lamps "+ 
	     "can be hung. The column surfaces are completely unmar"+ 
	     "red, and they seem to radiate warmth.\n");
    
    add_item(({"tome", "tomes", "book", "books"}), 
	     "The room is filled with books and tomes of every sort. "+ 
	     "They are mostly arranged on the shelves, but some lie "+ 
	     "opened upon the tables, the subject of study by some "+ 
	     "diligent knight. They all seem to be in fairly good condi"+ 
	     "tion, which must be the result of meticulous care as many "+ 
	     "of the volumes are centuries old.\n");
    
    add_item(({"scrolls", "scroll", "writing", "ink", "script"}), 
	     "There are countless scrolls in this place, the result of "+ 
	     "many decades of research and wisdom. They are in a "+ 
	     "wide variety of handwriting as well, ranging from a "+ 
	     "thin, spidery writing in blood-red ink, to a soft and flow"+ 
	     "ing script in a morocco shade of blue. Sadly, the wis"+ 
	     "dom of these scrolls is beyond your comprehension--"+ 
	     "for the time being at least.\n");
    
    add_item(({"shelves", "shelf"}), 
	     "The shelves are made of dark, strong oak that has "+ 
	     "been weathered for a long time. Upon the shelves lie "+ 
	     "the newer scrolls along with many tomes of a variety "+ 
	     "of shapes and sizes, arranged neatly in some places, "+ 
	     "and haphazardly strewn about a shelf in others. There "+
	     "is not a speck of dust anywhere on the shelves.\n");
    
    add_item(({"floor", "circle", "marble", "center"}), 
	     "The floor is of a glassy, polished marble that has thin "+ 
	     "veins of blue stone circling about in random patterns. "+ 
	     "Before the podium is a large circle engraved in the floor, "+ 
	     "within which are stylized images of a sword and a rose. "+ 
	     "The stone of the floor somehow mutes your footsteps "+ 
	     "and makes walking here noiseless.\n");
    
    add_item(({"cabinets", "cabinet", "door", "glass"}), 
	     "The cabinets are of a light, sweet-smelling pine. They "+ 
	     "are intricatly carved with chains of roses that run along "+ 
	     "the side of the frame. The doors of the cabinets are "+ 
	     "glass, and within you can see the older scrolls care"+ 
	     "fully arranged and preserved. The doors to the cabinets "+ 
	     "have tiny bejeweled locks.\n");        
    
    add_item(({"lock", "locks", "jewel", "jewels"}), 
	     "These tiny locks are rather interesting in that there "+ 
	     "aren't any apparent mechanisms for unlocking them. "+ 
	     "There are small jewels set into the metal of the locks "+ 
	     "in a seemingly random pattern. They glow with an inner "+ 
	     "light and seem to be more than purely ornamental.\n");
    
    add_item(({"table", "tables", "chair"}), 
	     "Made of prized vallenwood from Solace, the tables and "+ 
	     "chairs are both functional and ornamental. Each is carv"+ 
	     "ed in a unique design of stylized and fancifcul creatures. "+ 
	     "Most of the chairs are pulled up to the tables, but a few "+ 
	     "look recently vacated. The table tops gleam mellowly in "+ 
	     "the diffuse light.\n");
    
    add_item(({"podium"}), 
	     "This is a simple podium made of white ash. The slanting "+ 
	     "surface is engraved with odd symbols, none of which are "+
	     "familiar to you. The sides are smooth and pale as flesh, "+ 
	     "and completely bare of ornamentation.\nThere is a placard "+
	     "resting atop it.\n");
    
    add_item(({"placard", "sign", "poster", "card"}),
	     "There are many words written upon it.\n");
    add_prop(OBJ_S_WIZINFO, "@@wizinfo");
    add_prop(ROOM_I_NO_ATTACK,1);
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, 2);
 
    AE(ROOM + "hp8", "north", 0);
    reset_spur_room();
    create_skill_raise();
    set_up_skills();
 
    set_tell_time(300);
    add_tell("You feel the presence of something vibrant and "+
        "joyful that raises spirits and strengthens hope.\n");

}

/*
 * Read the placard for training
 */
int
read(string str)
{
   NF("Read what? The placard?\n");
   if (str != "placard")      
      return 0;

   write("The placard reads:\n");
   if (MEMBER(TP) || LAYMAN(TP))
      write(""+
        "  *====================================================================*\n"+
        "      Here is the place where dedicated Knights of the Sword and Rose\n"+
        "   may learn the skills needed to become the proper vessels through\n"+
        "   which Paladine and his Sons may act.\n\n"+
        "      It is the wish of those Clerics of Paladine who teach here that\n"+
        "   all Knights who seek investiture be aware of the following:\n\n"+
        "   The Powers of the Gods are such that ordinary mortals cannot simply\n"+
        "   use them, but must be properly trained, lest their very essence be\n"+
        "   burned from them.\n"+
        "   Seek to learn what we teach only after periods spent in contemplation.\n"+
        "   The mind must be clear and the soul purged so that you stand before\n"+
        "   Kiri-Jolith as a vessel emptied of all it once contained, purified\n"+
        "   and seeking to be filled anew.\n"+
        "   Only in this way will you learn all that you must in order to become\n"+
        "   a true Cleric of Paladine. This you can become, as surely as you are\n"+
        "   also a Knight of Solamnia.\n"+
        "  *=====================================================================*\n");
      else
         write(""+
        "  *====================================================================*\n"+
        "      Here is the place where dedicated Knights of the Sword and Rose\n"+
        "   may learn the skills needed to become the proper vessels through\n"+
        "   which Paladine and his Sons may act.\n"+
        "   (Words you are unable to decipher follow for a paragraph or two.)\n"+
        "  *=====================================================================*\n");
   say(QCTNAME(TP) + " reads the placard on the podium.\n");
   return 1;
}



string 
wizinfo()
{
   return ("This is the magic skill training room of the Solamnian Knights. "+
           "If there should be cause to close down the training room, "+
           "do so by typing:  Call here close_guild\n"+
           "This will temporarily prevent mortals from entering. After a "+
           "reboot, the room will be open by default\n Please send the "+
           "Guildmaster and Liege mail if there is anything that needs "+
           "to be fixed.\n\n");
}

reset_spur_room()
{
    object trainer = present("cleric", TO);
    if (!objectp(trainer))
      {
	        trainer = clone_object(SNPC + "cleric");
         trainer->move_living("into the room", this_object());
    }                                                                
}                                                                    
                                                                     

void 
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if (interactive(ob))
      start_room_tells();

    if (!closed)
        return;

    if (ob->query_wiz_level())
        write("\n\nTHIS ROOM IS CLOSED!\nYou should come "+
            "back later. This area is under construction.\n");
    else
    {
        write("Some magical force propels you from the room!\n");
	ob->move(ROOM + "hp8");
    }
}

string 
close_guild()
{
    if (closed)
    {
        closed = 0;
        return "  **The guild is now open**";
    }
    closed = 1;
    return "  **The guild is now closed**";
}

int query_closed() { return closed; }

void
init()
{
    init_skill_raise();
    ::init();
    ADA("read");
}

void
set_up_skills()
{
   /*
    * Total levels (350) - common max (120) = taxed levels (230)
    * (50 * 3) + 30 + (2 * 25) = 230
    * Tax = 1% for 60 levels over common max
    *  230 / 60 = 3.83   Tax = 4%
    */
    sk_add_train(SS_ELEMENT_LIFE,     
                        "properly use the elements of Life",  0, 0, 50 );
    sk_add_train(SS_FORM_ENCHANTMENT, 
                        "properly work enchantments",         0, 0, 50 );
    sk_add_train(SS_FORM_DIVINATION,  
                     "communicate with the gods",             0, 0, 50 );
    sk_add_train(SS_SPELLCRAFT,       
                     "understand magic",                      0, 0, 50 );
    sk_add_train(SS_LANGUAGE,                                
                        "understand and use arcane languages", 
                        0, 0, 75);
    sk_add_train(SS_AWARENESS,
                        "remain aware of surroundings while working magic",
                        0, 0, 75);
}

int
sk_improve(string sk)
{
    if (sk)
      {
	  if ((!MEMBER(TP)) || (MEMBER(TP) && TP->query_knight_level() < 4))
	    {
		NF("Only Solamnian Knights belonging to the Orders of "+
		     "Sword and Rose may train here.\n");
		return 1;
	    }
      }
    if (!(present("cleric", this_object())))
      {
	  write("The cleric of Paladine is not here to train you.\n");
	  return 1;
      }
    if (REALAGE(TP) < TP->query_skill(SS_DISGRACED))                
      {                                                             
          write("You are in disgrace and thus banned from training!\n");
          return 1;                                                          
      }                                                                      
    TP->remove_skill(SS_DISGRACED);                                          
                                                                                                                                                
    return ::sk_improve(sk);                                                 
}                                                                            
                                                                             
                                                                                                           
/* Borrowed from Olorin's ~Gondor/common/guild2/trainhall.c */
varargs int
sk_query_max(int sknum, int silent)
{
    int     occup_stat,
            stat_max = 90,
            max, *skills_available_here;
    object pl;
    
    if (!this_player() || ((this_player() != previous_object()) &&
			   previous_object() != this_object()))
	pl = previous_object();
    else
	pl = this_player();

    occup_stat = pl->query_stat(SS_OCCUP);

    /* Added to adapt to the skill_decay function.            */
    /* If a skill isn't available here, this function should  */
    /* return 0.               Jeremiah, 95/07/09             */

    skills_available_here = sk_query_train();

    if(member_array(sknum, skills_available_here) == -1)
        return 0;


    if (member_array(sknum,SS_MAGIC_ELEMENTS) >= 0)
    {
        stat_max = pl->query_stat(SS_INT);
    }
    else if (member_array(sknum, SS_MAGIC_FORMS) >= 0)
    {
        stat_max = pl->query_stat(SS_WIS);
    }

    if (stat_max > occup_stat)
        stat_max = occup_stat;

    max = ::sk_query_max(sknum, silent);

    return (stat_max > max ? max : stat_max);
}

int
sk_hook_improved_max(string skill)
{
    notify_fail("You cannot raise this skill any further here, you have to\n" +
		"seek knowledge elsewhere.\n");
    return 0;
}

