#include <tasks.h>
#include <macros.h>
#include <ss_types.h>
#include <composite.h>
#include "../nov.h"
#include <stdproperties.h>

inherit "/std/object";

int labuse;

void 
create_object()
{
        set_name("workbench");
        set_adj("wooden");
        add_adj("laboratory");
        set_short("wooden laboratory workbench");
        
        set_long("This is a wooden laboratory workbench. It is filled with " +
        "vials, spiral glass-tubes, mortars, jars and a magical heater. Different " +
        "types of potions and brews can be created by distilling different components with " +
        "the proper skill and patience.\n");

        add_prop(OBJ_M_NO_GET,"No, you would not even dare to nudge this laboratory " +
        "workbench with all the very expensive equipment on it.\n");
        
        labuse = 0;
        
        setuid();
        seteuid(getuid());
}

void
reset_lab()
{
	labuse = 0;
}



int
grind_comp(string str)
{
	
	object paralyze, comp;
	
	
        object *gems = filter(deep_inventory(this_player()), &operator(==)("onyx") @&->query_gem_name());
        
        



	if (!str)
	{
		write("Grind what with the heavy stone-mortar?\n");
		return 1;
	}
	
	if (str == "onyx")
	{
		// tresprit text mekking etc "wood spirits"
		
		 if (labuse == 1)
            {
            	write("The laboratory is already occupied by someone else doing laboratory work!\n");
            	return 1;
            }
        
		
            if (!sizeof(gems))
            {
               write("You dont have an onyx.\n");
             return 1;
             }
    
            comp = gems[0];
    
            comp->set_heap_size(comp->num_heap() - 1);
		
	    write("You prepare to grind an onyx!\n");

            tell_room(environment(this_player()), QCTNAME(this_player())+" begins " +
            "preparing for processing something.\n", this_player());
            
            labuse = 1;
            
            paralyze = clone_object("/std/paralyze");
            paralyze -> set_remove_time(46);
            paralyze -> set_fail_message("You are busy doing laboratory work!\n");
            paralyze -> set_stop_message("You finish the laboratory work.\n");
            paralyze -> move(this_player(), 1);
        
 
            set_alarm(3.0,0.0, &tell_room(environment(this_object()), QCTNAME(this_player())+" puts an " +
            "onyx into the heavy stone mortar.\n", this_player()));                 
            set_alarm(3.0,0.0, &write("You put an onyx into the heavy stone mortar.\n"));
            
            set_alarm(6.0,0.0, &tell_room(environment(this_object()), QCTNAME(this_player())+" grabs a " +
            "heavy stone-pestle from the workbench and holds it firmly while lowering it " +
            "into the heavy stone mortar.\n", this_player()));                 
            set_alarm(6.0,0.0, &write("You grab a heavy stone-pestle from the workbench " +
            "and you hold it firmly as you lowers it into the heavy stone mortar.\n"));
            
            set_alarm(9.0,0.0, &tell_room(environment(this_object()), QCTNAME(this_player())+" begins " +
            "to grind the onyx with "+this_player()->query_possessive()+" heavy stone-pestle.\n", this_player()));                 
            set_alarm(9.0,0.0, &write("You begin to grind the onyx with your heavy stone-pestle.\n"));
            
            set_alarm(15.0,0.0, &tell_room(environment(this_object()), QCTNAME(this_player())+" grinds " +
            "the onyx into tiny bits.\n", this_player()));                 
            set_alarm(15.0,0.0, &write("You grind the onyx into tiny bits.\n"));
            
             set_alarm(25.0,0.0, &tell_room(environment(this_object()), QCTNAME(this_player())+" grinds " +
            "the onyx into dust.\n", this_player()));                 
            set_alarm(25.0,0.0, &write("You grind the onyx into dust.\n"));
            
            
            set_alarm(35.0,0.0, &tell_room(environment(this_object()), QCTNAME(this_player())+" puts the " +
            "heavy stone-pestle back at the workbench, and picks up the onyx-dust from the " +
            "heavy stone mortar.\n", this_player()));                 
            set_alarm(35.0,0.0, &write("You put the heavy stone-pestle back onto the " +
            "workbench, and picks up the onyx-dust from the heavy stone mortar.\n"));

            clone_object(NOV_DIR +"obj/onyx_dust")->move(this_player(), 1);


            set_alarm(36.0,0.0, &reset_lab());
             
             return 1;
        }


        if (str == "kneecap")
	{
		// tresprit text mekking etc "wood spirits"
		
		 if (labuse == 1)
            {
            	write("The laboratory is already occupied by someone else doing laboratory work!\n");
            	return 1;
            }
        
        
           
            
            if(!present("kneecap", this_player()))
               {
                  write("You dont have a kneecap.\n");
                  return 1;
               }
               
            if(present("kneecap",this_player()))
               {
                  present("kneecap",this_player())->remove_object();
               }

            
	    write("You prepare to grind a kneecap!\n");

            tell_room(environment(this_player()), QCTNAME(this_player())+" begins " +
            "preparing for processing something.\n", this_player());
            
            labuse = 1;
            
            paralyze = clone_object("/std/paralyze");
            paralyze -> set_remove_time(46);
            paralyze -> set_fail_message("You are busy doing laboratory work!\n");
            paralyze -> set_stop_message("You finish the laboratory work.\n");
            paralyze -> move(this_player(), 1);
        
 
            set_alarm(3.0,0.0, &tell_room(environment(this_object()), QCTNAME(this_player())+" puts a " +
            "kneecap into the heavy stone mortar.\n", this_player()));                 
            set_alarm(3.0,0.0, &write("You put a kneecap into the heavy stone mortar.\n"));
            
            set_alarm(6.0,0.0, &tell_room(environment(this_object()), QCTNAME(this_player())+" grabs a " +
            "heavy stone-pestle from the workbench and holds it firmly while lowering it " +
            "into the heavy stone mortar.\n", this_player()));                 
            set_alarm(6.0,0.0, &write("You grab a heavy stone-pestle from the workbench " +
            "and you hold it firmly as you lowers it into the heavy stone mortar.\n"));
            
            set_alarm(9.0,0.0, &tell_room(environment(this_object()), QCTNAME(this_player())+" begins " +
            "to grind the kneecap with "+this_player()->query_possessive()+" heavy stone-pestle.\n", this_player()));                 
            set_alarm(9.0,0.0, &write("You begin to grind the kneecap with your heavy stone-pestle.\n"));
            
            set_alarm(15.0,0.0, &tell_room(environment(this_object()), QCTNAME(this_player())+" grinds " +
            "the kneecap into tiny bits.\n", this_player()));                 
            set_alarm(15.0,0.0, &write("You grind the kneecap into tiny bits.\n"));
            
             set_alarm(25.0,0.0, &tell_room(environment(this_object()), QCTNAME(this_player())+" grinds " +
            "the kneecap into powder.\n", this_player()));                 
            set_alarm(25.0,0.0, &write("You grind the kneecap into powder.\n"));
            
            
            set_alarm(35.0,0.0, &tell_room(environment(this_object()), QCTNAME(this_player())+" puts the " +
            "heavy stone-pestle back at the workbench, and picks up the bone-powder from the " +
            "heavy stone mortar.\n", this_player()));                 
            set_alarm(35.0,0.0, &write("You put the heavy stone-pestle back onto the " +
            "workbench, and picks up the bone-powder from the heavy stone mortar.\n"));

            clone_object(NOV_DIR +"obj/bone_powder")->move(this_player(), 1);


            set_alarm(36.0,0.0, &reset_lab());
             
             return 1;
        }


	return 1;
}


int
make_comp(string str)
{
	
	object paralyze;
	
	
	
	
	
	
	if (!str)
	{
		
		return 0;
	}
	
	if (str == "methyl")
	{
		// tresprit text mekking etc "wood spirits"
		
		
            if (labuse == 1)
            {
            	write("The laboratory is already occupied by someone else doing laboratory work!\n");
            	return 1;
            }
        
		
	    write("You prepare to distill methyl!\n");

            tell_room(environment(this_player()), QCTNAME(this_player())+" begins " +
            "preparing for processing something.\n", this_player());
            
            labuse = 1;
            
            paralyze = clone_object("/std/paralyze");
            paralyze -> set_remove_time(115);
            paralyze -> set_fail_message("You are busy doing laboratory work!\n");
            paralyze -> set_stop_message("You finish the laboratory work.\n");
            paralyze -> move(this_player(), 1);
        
 
            set_alarm(3.0,0.0, &tell_room(environment(this_object()), QCTNAME(this_player())+" turns on " +
            "the magical heater. The magical heater burns with a green clear flame.\n", this_player()));                 
            set_alarm(3.0,0.0, &write("You turn on the magical heater. The magical heater burns with " +
            "a green clear flame.\n"));

      
            set_alarm(6.0,0.0, &tell_room(environment(this_object()), QCTNAME(this_player())+" puts some sawdust " +
            "into a glass vial, and connects its muzzle to a large spiral glass-tube.\n", this_player()));            
            set_alarm(6.0,0.0, &write("You put some sawdust into a glass vial, and connect its muzzle to " +
            "a large spiral glass-tube.\n"));
            
            
            set_alarm(10.0,0.0, &tell_room(environment(this_object()), QCTNAME(this_player())+" carefully " +
            "places the glass vial containing sawdust onto the magical heater.\n", this_player()));
            set_alarm(10.0,0.0, &write("You carefully place the glass vial containing sawdust " +
            "onto the magical heater.\n"));
            
            set_alarm(20.0,0.0, &tell_room(environment(this_object()), "The glass vial containing sawdust begins " +
            "to be filled with white-grey smoke and moist extracted from the sawdust. The smoke begins to fill the spiral " +
            "glass-tubes connected to the glass vial.\n"));
          
            
            set_alarm(30.0,0.0, &tell_room(environment(this_object()), "The smoke and the moist in the " +
            "spiral glass-tubes begins to cool off. Small drops of a clear liquid begins to drop from " +
            "the rear of the spiral glass-tube, down into a glass jar.\n"));
            
            set_alarm(35.0,0.0, &tell_room(environment(this_object()), "Small drops of a clear " +
            "liquid drops from the rear of the spiral glass-tube, down into a glass jar.\n"));
            
            set_alarm(40.0,0.0, &tell_room(environment(this_object()), "Small drops of a clear " +
            "liquid drops from the rear of the spiral glass-tube, down into a glass jar.\n"));
            
            set_alarm(45.0,0.0, &tell_room(environment(this_object()), "Small drops of a clear " +
            "liquid drops from the rear of the spiral glass-tube, down into a glass jar.\n"));
            
            set_alarm(50.0,0.0, &tell_room(environment(this_object()), "Small drops of a clear " +
            "liquid drops from the rear of the spiral glass-tube, down into a glass jar.\n"));
            
            set_alarm(55.0,0.0, &tell_room(environment(this_object()), "Small drops of a clear " +
            "liquid drops from the rear of the spiral glass-tube, down into a glass jar.\n"));
            
            set_alarm(60.0,0.0, &tell_room(environment(this_object()), "Small drops of a clear " +
            "liquid drops from the rear of the spiral glass-tube, down into a glass jar.\n"));
            
            set_alarm(65.0,0.0, &tell_room(environment(this_object()), "Small drops of a clear " +
            "liquid drops from the rear of the spiral glass-tube, down into a glass jar.\n"));
            
            set_alarm(70.0,0.0, &tell_room(environment(this_object()), "Small drops of a clear " +
            "liquid drops from the rear of the spiral glass-tube, down into a glass jar.\n"));
            
            set_alarm(75.0,0.0, &tell_room(environment(this_object()), "Small drops of a clear " +
            "liquid drops from the rear of the spiral glass-tube, down into a glass jar.\n"));
            
            set_alarm(80.0,0.0, &tell_room(environment(this_object()), "Small drops of a clear " +
            "liquid drops from the rear of the spiral glass-tube, down into a glass jar.\n"));
            
            set_alarm(85.0,0.0, &tell_room(environment(this_object()), "Small drops of a clear " +
            "liquid drops from the rear of the spiral glass-tube, down into a glass jar.\n"));
            
            set_alarm(90.0,0.0, &tell_room(environment(this_object()), "Small drops of a clear " +
            "liquid drops from the rear of the spiral glass-tube, down into a glass jar.\n"));
            
            set_alarm(95.0,0.0, &tell_room(environment(this_object()), "Small drops of a clear " +
            "liquid drops from the rear of the spiral glass-tube, down into a glass jar.\n"));
            
            set_alarm(105.0,0.0, &tell_room(environment(this_object()), "The glass jar is now " +
            "full of a clear liquid. "+QCTNAME(this_player())+" moves the smoke-grey glass vial from " +
            "the magical heater and begins to clean away the black remains of the sawdust in it.\n", this_player()));            
            set_alarm(105.0,0.0, &write("The glass jar is now filled with a clear liquid. You move the smoke-grey " +
            "glass vial from the magical heater and begin to clean away the black remains of the sawdust in it.\n"));
            
            set_alarm(110.0,0.0, &tell_room(environment(this_object()), QCTNAME(this_player())+" turns off " +
            "the magical heater.\n", this_player()));            
            set_alarm(110.0,0.0, &write("You turn off the magical heater.\n"));
            
            set_alarm(114.0,0.0, &tell_room(environment(this_object()), QCTNAME(this_player())+" gets the " +
            "filled glass jar and pours the clear liquid into five tiny " +
            "vials.\n"+QCTNAME(this_player())+" gently puts the empty glass jar back onto the workbench, and picks " +
            "up the tiny vials with the liquid.", this_player()));            
            set_alarm(114.0,0.0, &write("You get the filled glass jar and pour the clear liquid into five " +
            "tiny vials.\nYou gently put the empty glass jar back onto the workbench, and pick up the " +
            "tiny vials.\n"));
            
            clone_object(NOV_DIR +"obj/methyl")->move(this_player(), 1);
            clone_object(NOV_DIR +"obj/methyl")->move(this_player(), 1);
            clone_object(NOV_DIR +"obj/methyl")->move(this_player(), 1);
            clone_object(NOV_DIR +"obj/methyl")->move(this_player(), 1);
            clone_object(NOV_DIR +"obj/methyl")->move(this_player(), 1);
            
             set_alarm(115.0,0.0, &reset_lab());
             
             return 1;
        }
        
	
	
	
	if (str == "nerulla")
	{
		
		
            if (labuse == 1)
            {
            	write("The laboratory is already occupied by someone else doing laboratory work!\n");
            	return 1;
            }
        
        
           if(!present("skullcap", this_player()))
               {
                  write("You don't have a skullcap.\n");
                  return 1;
               }
               
           if(!present("angurth", this_player()))
               {
                  write("You don't have an angurth.\n");
                  return 1;
               }
               
               //***********    
               
            if(present("skullcap",this_player()))
               {
                  present("skullcap",this_player())->remove_object();
               }
            
            if(present("angurth",this_player()))
               {
                  present("angurth",this_player())->remove_object();
               }
        
        
		
	    write("You prepare to brew nerulla!\n");

            tell_room(environment(this_player()), QCTNAME(this_player())+" begins " +
            "preparing to brew something.\n", this_player());
            
            labuse = 1;
            
            paralyze = clone_object("/std/paralyze");
            paralyze -> set_remove_time(146);
            paralyze -> set_fail_message("You are busy doing laboratory work!\n");
            paralyze -> set_stop_message("You finish the laboratory work.\n");
            paralyze -> move(this_player(), 1);
        
 
            set_alarm(3.0,0.0, &tell_room(environment(this_object()), QCTNAME(this_player())+" turns on " +
            "the magical heater. The magical heater burns with a green clear flame.\n", this_player()));                 
            set_alarm(3.0,0.0, &write("You turn on the magical heater. The magical heater burns with " +
            "a green clear flame.\n"));

      
            set_alarm(6.0,0.0, &tell_room(environment(this_object()), QCTNAME(this_player())+" fills a " +
            "glass bottle with some water.\n", this_player()));            
            set_alarm(6.0,0.0, &write("You fill a glass bottle with some water.\n"));
            
            set_alarm(9.0,0.0, &tell_room(environment(this_object()), QCTNAME(this_player())+" puts the " +
            "glass bottle onto the magical heater.\n", this_player()));            
            set_alarm(9.0,0.0, &write("You put the glass bottle onto the magical heater.\n"));
            
             set_alarm(14.0,0.0, &tell_room(environment(this_object()), QCTNAME(this_player())+" puts some " +
             "ingredients into the glass bottle, which is slowly heating up.\n", this_player()));            
            set_alarm(14.0,0.0, &write("You put your readied ingredients into the glass bottle, which is slowly " +
            "heating up.\n"));
        
            set_alarm(20.0,0.0, &tell_room(environment(this_object()), "The glass bottle on the " +
            "magical heater begins to boil.\n"));
            
            set_alarm(30.0,0.0, &tell_room(environment(this_object()), "The glass bottle on the " +
            "magical heater boils, giving away a rustling sound as tiny bubbles pops on the inside.\n"));
            
            set_alarm(40.0,0.0, &tell_room(environment(this_object()), "The glass bottle on the " +
            "magical heater boils, giving away a rustling sound as tiny bubbles pops on the inside.\n"));
            
            set_alarm(50.0,0.0, &tell_room(environment(this_object()), "The glass bottle on the " +
            "magical heater boils, giving away a rustling sound as tiny bubbles pops on the inside.\n"));
            
            set_alarm(60.0,0.0, &tell_room(environment(this_object()), "The glass bottle on the " +
            "magical heater boils, giving away a rustling sound as tiny bubbles pops on the inside.\n"));
            
            set_alarm(70.0,0.0, &tell_room(environment(this_object()), "The glass bottle on the " +
            "magical heater boils, giving away a rustling sound as tiny bubbles pops on the inside.\n"));
            
            set_alarm(80.0,0.0, &tell_room(environment(this_object()), "The glass bottle on the " +
            "magical heater boils, giving away a rustling sound as tiny bubbles pops on the inside.\n"));
            
            set_alarm(90.0,0.0, &tell_room(environment(this_object()), "The glass bottle on the " +
            "magical heater boils, giving away a rustling sound as tiny bubbles pops on the inside.\n"));
            
            set_alarm(100.0,0.0, &tell_room(environment(this_object()), "The glass bottle on the " +
            "magical heater boils, giving away a rustling sound as tiny bubbles pops on the inside.\n"));
            
            set_alarm(110.0,0.0, &tell_room(environment(this_object()), "The glass bottle on the " +
            "magical heater boils, giving away a rustling sound as tiny bubbles pops on the inside.\n"));
            
            set_alarm(120.0,0.0, &tell_room(environment(this_object()), "The glass bottle on the " +
            "magical heater boils, giving away a rustling sound as tiny bubbles pops on the inside.\n"));
            
            set_alarm(130.0,0.0, &tell_room(environment(this_object()), QCTNAME(this_player())+" turns off " +
            "the magical heater, as the brew is near completion.\n", this_player()));            
            set_alarm(130.0,0.0, &write("You turn off the magical heater, as the brew is near completion.\n"));
            
            set_alarm(140.0,0.0, &tell_room(environment(this_object()), "The glass bottle cools " +
            "down, giving away some dampened sounds of tiny bubbles popping inside.\n"));
            
            set_alarm(145.0,0.0, &tell_room(environment(this_object()), QCTNAME(this_player())+" takes an " +
            "empty vial from the workbench and fills it with a jet-black rustling liquid from " +
            "the glass bottle.\n", this_player()));    
            set_alarm(145.0,0.0, &write("You take an empty vial from the workbench and fill it with a " +
            "jet-black rustling liquid from the glass bottle.\n"));
           
            clone_object(NOV_DIR +"obj/potion1")->move(this_player(), 1);
            
            set_alarm(146.0,0.0, &reset_lab());
          
		
		return 1;
	}
	
	
	if (str == "otawine")
	{
		
		
            if (labuse == 1)
            {
            	write("The laboratory is already occupied by someone else doing laboratory work!\n");
            	return 1;
            }
        
		
		
            if(!present("sumac", this_player()))
               {
                  write("You don't have a sumac.\n");
                  return 1;
               }
               
               
               if(!present("pepper", this_player()))
               {
                  write("You don't have a pepper.\n");
                  return 1;
               }
               
               //******************
               
               
            if(present("sumac",this_player()))
               {
                  present("sumac",this_player())->remove_object();
               }
               
            if(present("pepper",this_player()))
               {
                  present("pepper",this_player())->remove_object();
               }
		
		
	    write("You prepare to brew otawine!\n");

            tell_room(environment(this_player()), QCTNAME(this_player())+" begins " +
            "preparing to brew something.\n", this_player());
            
            labuse = 1;
            
            paralyze = clone_object("/std/paralyze");
            paralyze -> set_remove_time(146);
            paralyze -> set_fail_message("You are busy doing laboratory work!\n");
            paralyze -> set_stop_message("You finish the laboratory work.\n");
            paralyze -> move(this_player(), 1);
        
 
            set_alarm(3.0,0.0, &tell_room(environment(this_object()), QCTNAME(this_player())+" turns on " +
            "the magical heater. The magical heater burns with a green clear flame.\n", this_player()));                 
            set_alarm(3.0,0.0, &write("You turn on the magical heater. The magical heater burns with " +
            "a green clear flame.\n"));

      
            set_alarm(6.0,0.0, &tell_room(environment(this_object()), QCTNAME(this_player())+" fills a " +
            "glass bottle with some water.\n", this_player()));            
            set_alarm(6.0,0.0, &write("You fill a glass bottle with some water.\n"));
            
            set_alarm(9.0,0.0, &tell_room(environment(this_object()), QCTNAME(this_player())+" puts the " +
            "glass bottle onto the magical heater.\n", this_player()));            
            set_alarm(9.0,0.0, &write("You put the glass bottle onto the magical heater.\n"));
            
             set_alarm(14.0,0.0, &tell_room(environment(this_object()), QCTNAME(this_player())+" puts some " +
             "ingredients into the glass bottle, which is slowly heating up.\n", this_player()));            
            set_alarm(14.0,0.0, &write("You put your readied ingredients into the glass bottle, which is slowly " +
            "heating up.\n"));
        
            set_alarm(20.0,0.0, &tell_room(environment(this_object()), "The glass bottle on the " +
            "magical heater begins to boil.\n"));
            
            set_alarm(30.0,0.0, &tell_room(environment(this_object()), "The glass bottle on the " +
            "magical heater boils, giving away a rustling sound as tiny bubbles pops on the inside.\n"));
            
            set_alarm(40.0,0.0, &tell_room(environment(this_object()), "The glass bottle on the " +
            "magical heater boils, giving away a rustling sound as tiny bubbles pops on the inside.\n"));
            
            set_alarm(50.0,0.0, &tell_room(environment(this_object()), "The glass bottle on the " +
            "magical heater boils, giving away a rustling sound as tiny bubbles pops on the inside.\n"));
            
            set_alarm(60.0,0.0, &tell_room(environment(this_object()), "The glass bottle on the " +
            "magical heater boils, giving away a rustling sound as tiny bubbles pops on the inside.\n"));
            
            set_alarm(70.0,0.0, &tell_room(environment(this_object()), "The glass bottle on the " +
            "magical heater boils, giving away a rustling sound as tiny bubbles pops on the inside.\n"));
            
            set_alarm(80.0,0.0, &tell_room(environment(this_object()), "The glass bottle on the " +
            "magical heater boils, giving away a rustling sound as tiny bubbles pops on the inside.\n"));
            
            set_alarm(90.0,0.0, &tell_room(environment(this_object()), "The glass bottle on the " +
            "magical heater boils, giving away a rustling sound as tiny bubbles pops on the inside.\n"));
            
            set_alarm(100.0,0.0, &tell_room(environment(this_object()), "The glass bottle on the " +
            "magical heater boils, giving away a rustling sound as tiny bubbles pops on the inside.\n"));
            
            set_alarm(110.0,0.0, &tell_room(environment(this_object()), "The glass bottle on the " +
            "magical heater boils, giving away a rustling sound as tiny bubbles pops on the inside.\n"));
            
            set_alarm(120.0,0.0, &tell_room(environment(this_object()), "The glass bottle on the " +
            "magical heater boils, giving away a rustling sound as tiny bubbles pops on the inside.\n"));
            
            set_alarm(130.0,0.0, &tell_room(environment(this_object()), QCTNAME(this_player())+" turns off " +
            "the magical heater, as the brew is near completion.\n", this_player()));            
            set_alarm(130.0,0.0, &write("You turn off the magical heater, as the brew is near completion.\n"));
            
           set_alarm(140.0,0.0, &tell_room(environment(this_object()), "The glass bottle cools " +
            "down, giving away some dampened sounds of tiny bubbles popping inside.\n"));
            
            set_alarm(145.0,0.0, &tell_room(environment(this_object()), QCTNAME(this_player())+" takes an " +
            "empty vial from the workbench and fills it with a blood-red rustling liquid from " +
            "the glass bottle.\n", this_player()));    
            set_alarm(145.0,0.0, &write("You take an empty vial from the workbench and fill it with a " +
            "blood-red rustling liquid from the glass bottle.\n"));
           
          
           
            clone_object(NOV_DIR +"obj/potion2")->move(this_player(), 1);
            
            set_alarm(146.0,0.0, &reset_lab());
          
		
		return 1;
	}
	
	if (str == "chrimin")
	{
		
		
            if (labuse == 1)
            {
            	write("The laboratory is already occupied by someone else doing laboratory work!\n");
            	return 1;
            }
        
		
	    if(!present("rosemary", this_player()))
               {
                  write("You don't have a rosemary.\n");
                  return 1;
               }
               
               if(!present("myrtleberry", this_player()))
               {
                  write("You don't have a myrtleberry.\n");
                  return 1;
               }
            
               
               
               //************
               
               
               
             
             
             
             if(present("rosemary",this_player()))
               {
                  present("rosemary",this_player())->remove_object();
               }
              
            if(present("myrtleberry",this_player()))
               {
                  present("myrtleberry",this_player())->remove_object();
               }
		
	    write("You prepare to brew chrimin!\n");

            tell_room(environment(this_player()), QCTNAME(this_player())+" begins " +
            "preparing to brew something.\n", this_player());
            
            labuse = 1;
            
            paralyze = clone_object("/std/paralyze");
            paralyze -> set_remove_time(146);
            paralyze -> set_fail_message("You are busy doing laboratory work!\n");
            paralyze -> set_stop_message("You finish the laboratory work.\n");
            paralyze -> move(this_player(), 1);
        
 
            set_alarm(3.0,0.0, &tell_room(environment(this_object()), QCTNAME(this_player())+" turns on " +
            "the magical heater. The magical heater burns with a green clear flame.\n", this_player()));                 
            set_alarm(3.0,0.0, &write("You turn on the magical heater. The magical heater burns with " +
            "a green clear flame.\n"));

      
            set_alarm(6.0,0.0, &tell_room(environment(this_object()), QCTNAME(this_player())+" fills a " +
            "glass bottle with some water.\n", this_player()));            
            set_alarm(6.0,0.0, &write("You fill a glass bottle with some water.\n"));
            
            set_alarm(9.0,0.0, &tell_room(environment(this_object()), QCTNAME(this_player())+" puts the " +
            "glass bottle onto the magical heater.\n", this_player()));            
            set_alarm(9.0,0.0, &write("You put the glass bottle onto the magical heater.\n"));
            
             set_alarm(14.0,0.0, &tell_room(environment(this_object()), QCTNAME(this_player())+" puts some " +
             "ingredients into the glass bottle, which is slowly heating up.\n", this_player()));            
            set_alarm(14.0,0.0, &write("You put your readied ingredients into the glass bottle, which is slowly " +
            "heating up.\n"));
        
            set_alarm(20.0,0.0, &tell_room(environment(this_object()), "The glass bottle on the " +
            "magical heater begins to boil.\n"));
            
            set_alarm(30.0,0.0, &tell_room(environment(this_object()), "The glass bottle on the " +
            "magical heater boils, giving away a rustling sound as tiny bubbles pops on the inside.\n"));
            
            set_alarm(40.0,0.0, &tell_room(environment(this_object()), "The glass bottle on the " +
            "magical heater boils, giving away a rustling sound as tiny bubbles pops on the inside.\n"));
            
            set_alarm(50.0,0.0, &tell_room(environment(this_object()), "The glass bottle on the " +
            "magical heater boils, giving away a rustling sound as tiny bubbles pops on the inside.\n"));
            
            set_alarm(60.0,0.0, &tell_room(environment(this_object()), "The glass bottle on the " +
            "magical heater boils, giving away a rustling sound as tiny bubbles pops on the inside.\n"));
            
            set_alarm(70.0,0.0, &tell_room(environment(this_object()), "The glass bottle on the " +
            "magical heater boils, giving away a rustling sound as tiny bubbles pops on the inside.\n"));
            
            set_alarm(80.0,0.0, &tell_room(environment(this_object()), "The glass bottle on the " +
            "magical heater boils, giving away a rustling sound as tiny bubbles pops on the inside.\n"));
            
            set_alarm(90.0,0.0, &tell_room(environment(this_object()), "The glass bottle on the " +
            "magical heater boils, giving away a rustling sound as tiny bubbles pops on the inside.\n"));
            
            set_alarm(100.0,0.0, &tell_room(environment(this_object()), "The glass bottle on the " +
            "magical heater boils, giving away a rustling sound as tiny bubbles pops on the inside.\n"));
            
            set_alarm(110.0,0.0, &tell_room(environment(this_object()), "The glass bottle on the " +
            "magical heater boils, giving away a rustling sound as tiny bubbles pops on the inside.\n"));
            
            set_alarm(120.0,0.0, &tell_room(environment(this_object()), "The glass bottle on the " +
            "magical heater boils, giving away a rustling sound as tiny bubbles pops on the inside.\n"));
            
            set_alarm(130.0,0.0, &tell_room(environment(this_object()), QCTNAME(this_player())+" turns off " +
            "the magical heater, as the brew is near completion.\n", this_player()));            
            set_alarm(130.0,0.0, &write("You turn off the magical heater, as the brew is near completion.\n"));
            
           set_alarm(140.0,0.0, &tell_room(environment(this_object()), "The glass bottle cools " +
            "down, giving away some dampened sounds of tiny bubbles popping inside.\n"));
            
            set_alarm(145.0,0.0, &tell_room(environment(this_object()), QCTNAME(this_player())+" takes an " +
            "empty vial from the workbench and fills it with a dark-blue rustling liquid from " +
            "the glass bottle.\n", this_player()));    
            set_alarm(145.0,0.0, &write("You take an empty vial from the workbench and fill it with a " +
            "dark-blue rustling liquid from the glass bottle.\n"));
           
            clone_object(NOV_DIR +"obj/potion3")->move(this_player(), 1);
            
            set_alarm(146.0,0.0, &reset_lab());
          
		
		return 1;
	}
	
	return 0;
}


/* object *gems = filter(deep_inventory(caster), &operator(==)("ruby") @ 
        &->query_gem_name());


    if (!sizeof(gems))
    {
        caster->catch_tell("You need a red ruby in order to successfully" +
            " cast this spell!\n");
        return ({ });
    }
    
    comp = gems[0];*/



/*if (random(100) >= 90)
    {
            caster->catch_tell("You sacrificed a red ruby.\n");
            comp->set_heap_size(comp->num_heap() - 1);
    }*/          






int
feed_skull(string str)
{
	if (str != "skull")
	{
		return 0;
	}
	
		
		
            if (labuse == 1)
            {
            	write("The laboratory is already occupied by someone else doing laboratory work!\n");
            	return 1;
            }
        
        
           if(!present("torch", this_player()))
               {
                  write("The skull refuses to chew anything but torches!\n");
                  return 1;
               }
               
           if(present("torch",this_player()))
               {
                  present("torch",this_player())->remove_object();
               }    

           tell_room(environment(this_object()), QCTNAME(this_player())+" carefully " +
           "puts a torch betveen the razor-sharp iron teeth of the skull placed on the " +
           "workbench.\nThe skull suddently begins to chew the torch, grinding " +
           "it entirely into a pile of sawdust, which falls into a small bowl beneath it.\n"+QCTNAME(this_player())+" gets " +
           "the pile of sawdust from the bowl.\n", this_player());    
            write("You carefully put a torch betveen the razor-sharp " +
            "iron teeth of the skull placed on the workbench.\nThe skull suddently begins to chew the torch, grinding " +
            "it entirely into a pile of sawdust, which falls into a small " +
            "bowl placed beneath it.\nYou get the pile of sawdust from the bowl.\n");
            
            clone_object(NOV_DIR +"obj/sawdust")->move(this_player(), 1);
            
            return 1;
}
        
int
do_distill(string str)
{
	
	object paralyze;
	
	
	if (!str)
	{
		
		return 0;
	}
	
	if (str == "methyl")
	{
		// tresprit text mekking etc "wood spirits"
		
		
            if (labuse == 1)
            {
            	write("The laboratory is already occupied by someone else doing laboratory work!\n");
            	return 1;
            }
        
        
            if(!present("sawdust", this_player()))
               {
                  write("In order to distill methyl, you need some sawdust!\n");
                  return 1;
               }
               
           if(present("sawdust",this_player()))
               {
                  present("sawdust",this_player())->remove_object();
               }    
        
		
	    write("You prepare to distill methyl!\n");

            tell_room(environment(this_player()), QCTNAME(this_player())+" begins " +
            "preparing for processing something.\n", this_player());
            
            labuse = 1;
            
            paralyze = clone_object("/std/paralyze");
            paralyze -> set_remove_time(115);
            paralyze -> set_fail_message("You are busy doing laboratory work!\n");
            paralyze -> set_stop_message("You finish the laboratory work.\n");
            paralyze -> move(this_player(), 1);
        
 
            set_alarm(3.0,0.0, &tell_room(environment(this_object()), QCTNAME(this_player())+" turns on " +
            "the magical heater. The magical heater burns with a green clear flame.\n", this_player()));                 
            set_alarm(3.0,0.0, &write("You turn on the magical heater. The magical heater burns with " +
            "a green clear flame.\n"));

      
            set_alarm(6.0,0.0, &tell_room(environment(this_object()), QCTNAME(this_player())+" puts some sawdust " +
            "into a glass vial, and connects its muzzle to a large spiral glass-tube.\n", this_player()));            
            set_alarm(6.0,0.0, &write("You put some sawdust into a glass vial, and connect its muzzle to " +
            "a large spiral glass-tube.\n"));
            
            
            set_alarm(10.0,0.0, &tell_room(environment(this_object()), QCTNAME(this_player())+" carefully " +
            "places the glass vial containing sawdust onto the magical heater.\n", this_player()));
            set_alarm(10.0,0.0, &write("You carefully place the glass vial containing sawdust " +
            "onto the magical heater.\n"));
            
            set_alarm(20.0,0.0, &tell_room(environment(this_object()), "The glass vial containing sawdust begins " +
            "to be filled with white-grey smoke and moist extracted from the sawdust. The smoke begins to fill the spiral " +
            "glass-tubes connected to the glass vial.\n"));
          
            
            set_alarm(30.0,0.0, &tell_room(environment(this_object()), "The smoke and the moist in the " +
            "spiral glass-tubes begins to cool off. Small drops of a clear liquid begins to drop from " +
            "the rear of the spiral glass-tube, down into a glass jar.\n"));
            
            set_alarm(35.0,0.0, &tell_room(environment(this_object()), "Small drops of a clear " +
            "liquid drops from the rear of the spiral glass-tube, down into a glass jar.\n"));
            
            set_alarm(40.0,0.0, &tell_room(environment(this_object()), "Small drops of a clear " +
            "liquid drops from the rear of the spiral glass-tube, down into a glass jar.\n"));
            
            set_alarm(45.0,0.0, &tell_room(environment(this_object()), "Small drops of a clear " +
            "liquid drops from the rear of the spiral glass-tube, down into a glass jar.\n"));
            
            set_alarm(50.0,0.0, &tell_room(environment(this_object()), "Small drops of a clear " +
            "liquid drops from the rear of the spiral glass-tube, down into a glass jar.\n"));
            
            set_alarm(55.0,0.0, &tell_room(environment(this_object()), "Small drops of a clear " +
            "liquid drops from the rear of the spiral glass-tube, down into a glass jar.\n"));
            
            set_alarm(60.0,0.0, &tell_room(environment(this_object()), "Small drops of a clear " +
            "liquid drops from the rear of the spiral glass-tube, down into a glass jar.\n"));
            
            set_alarm(65.0,0.0, &tell_room(environment(this_object()), "Small drops of a clear " +
            "liquid drops from the rear of the spiral glass-tube, down into a glass jar.\n"));
            
            set_alarm(70.0,0.0, &tell_room(environment(this_object()), "Small drops of a clear " +
            "liquid drops from the rear of the spiral glass-tube, down into a glass jar.\n"));
            
            set_alarm(75.0,0.0, &tell_room(environment(this_object()), "Small drops of a clear " +
            "liquid drops from the rear of the spiral glass-tube, down into a glass jar.\n"));
            
            set_alarm(80.0,0.0, &tell_room(environment(this_object()), "Small drops of a clear " +
            "liquid drops from the rear of the spiral glass-tube, down into a glass jar.\n"));
            
            set_alarm(85.0,0.0, &tell_room(environment(this_object()), "Small drops of a clear " +
            "liquid drops from the rear of the spiral glass-tube, down into a glass jar.\n"));
            
            set_alarm(90.0,0.0, &tell_room(environment(this_object()), "Small drops of a clear " +
            "liquid drops from the rear of the spiral glass-tube, down into a glass jar.\n"));
            
            set_alarm(95.0,0.0, &tell_room(environment(this_object()), "Small drops of a clear " +
            "liquid drops from the rear of the spiral glass-tube, down into a glass jar.\n"));
            
            set_alarm(105.0,0.0, &tell_room(environment(this_object()), "The glass jar is now " +
            "full of a clear liquid. "+QCTNAME(this_player())+" moves the smoke-grey glass vial from " +
            "the magical heater and begins to clean away the black remains of the sawdust in it.\n", this_player()));            
            set_alarm(105.0,0.0, &write("The glass jar is now filled with a clear liquid. You move the smoke-grey " +
            "glass vial from the magical heater and begin to clean away the black remains of the sawdust in it.\n"));
            
            set_alarm(110.0,0.0, &tell_room(environment(this_object()), QCTNAME(this_player())+" turns off " +
            "the magical heater.\n", this_player()));            
            set_alarm(110.0,0.0, &write("You turn off the magical heater.\n"));
            
            set_alarm(114.0,0.0, &tell_room(environment(this_object()), QCTNAME(this_player())+" gets the " +
            "filled glass jar and pours the clear liquid into five tiny " +
            "vials.\n"+QCTNAME(this_player())+" gently puts the empty glass jar back onto the workbench, and picks " +
            "up the tiny vials with the liquid.", this_player()));            
            set_alarm(114.0,0.0, &write("You get the filled glass jar and pour the clear liquid into five " +
            "tiny vials.\nYou gently put the empty glass jar back onto the workbench, and pick up the " +
            "tiny vials.\n"));
            
            clone_object(NOV_DIR +"obj/methyl")->move(this_player(), 1);
            clone_object(NOV_DIR +"obj/methyl")->move(this_player(), 1);
            clone_object(NOV_DIR +"obj/methyl")->move(this_player(), 1);
            clone_object(NOV_DIR +"obj/methyl")->move(this_player(), 1);
            clone_object(NOV_DIR +"obj/methyl")->move(this_player(), 1);
            
             set_alarm(115.0,0.0, &reset_lab());
             
             return 1;
        }

      return 0;
}


void
init()
{
        ::init();
        add_action(make_comp, "brew");
        add_action(grind_comp, "grind");
        add_action(feed_skull, "feed");
        add_action(do_distill, "distill");
       
}

