//-*-C++-*-
// file name:      
// creator(s):     Lilith June 2008
// last update:    
// note: 
// bug(s):
// to-do:

#include "../guild.h";

inherit ROOM_DIR+"vamp_room";
inherit "/lib/commands";

#include <ss_types.h>
#include <composite.h>
#include <std.h>
#include <macros.h>
#include <language.h>

#define MATERIALS ({ "stone", "marble", "wood", "copper", "silver", \
                    "gold", "platinum", "steel", "adamantine", "brass", \
                    "bone", })

#define LININGS ({ "wool", "velvet", "silk", "satin", "suede", "leather", \
                    "linen", "chamois", "webcloth" })    

#define LINING_COLORS ({ "black", "blue", "cream", "gold", "green", \
                        "gray", "orange", "pink", "purple", "red", \
                        "white", "yellow", "gray" })  

public void create_vamp_room()
{

    set_short("Stone workshop");
    
    set_long("@@mylong@@");
    
    add_exit("outside","out");

    add_item(({"darkened scorched walls" , "soot", "darkened walls" , 
        "scorched walls" }),
        "Soot covers the walls, reaching toward the ceiling "+
        "like many-fingered hands trying to pull it down.  "+
        "Was there one great fire that caused all this damage?  "+
        "Or was it multiple fires? It is difficult to determine "+
        "for certain.  "+
        "\n");

    add_item(({"wall", "walls" }),
        "Which wall did you want to look at?\n");

    add_item(({"north wall" }),
        "The face of this wall is covered in racks that are "+
        "full of tools used for working stone and wood.  "+
        "\n");

    add_item(({"racks full of tools", "racks", "rack" }),
        "Some of the racks appear to be scorched a bit, others "+
        "appear to be recently added. "+
        "Each rack bears the tools and materials used for working "+
        "stone and wood.  "+
        "\n");

    add_item(({"tool", "tools" }),
        "These tools are well-made and in surprisingly good "+
        "repair given the seemingly neglected status of the "+
        "workshop itself.  "+
        "\n");

    add_item(({"various materials", "materials", "curious materials" }),
        "On the racks you can see a variety of materials "+
        "ranging from fabrics, to metals, wood, and stone.  "+
        "\n");

    add_item(({"metal", "metals", "steel", "adamantine" , "brass"}),
        "Here and there amongst the clutter on the racks "+
        "you can glimpse small amounts of metals that look "+
        "like steel, adamantine, and brass.\n");
                   
    add_item(({"fabric", "fabrics", "wool", "velvet", "silk" }),
        "Small rolls of fabric rest on the racks. "+
        "Peering closely, you think you can identify "+
        "bits of velvet, wool, and silk.\n");

    add_item(({"stones", "stone", "marble", "wood", "bone" }),
        "Lower on the racks are slabs of stone and marble, "+
        "as well as bone.\n");

    add_item(({"large furnace", "furnace" }),
        "On the east wall is a furnace that looks like it "+
        "is used to smelt metal. The furnace is very sturdy "+
        "and it appears to be undamaged by the fire that "+
        "swept through the workshop. The furnace radiates "+
        "heat, awaiting your use.\n");

    add_item(({"pull-out melting pot", "pot" , "melting pot" , 
        "pull-out pot", "smelting pot", "iron pot"}),
        "A very heavy pot made of thick slabs of iron.  "+
        "Traces of a variety of metals cling to the lip "+
        "of the pot, which apparently is designed for "+
        "smelting metals.\n");

    add_item(({"east wall"}),
        "The entire east wall is actually one face of a "+
        "large furnace.\n");
   
    add_item(({"west wall", "south wall"}),
        "It is grimy and soot-streaked like the other walls.\n");
 
    add_item(({"large wooden window frames", "large window frames",
        "window frames", "large window frames", "large windows", 
        "wooden window frames", "windows"}),
        "Large wooden window frames line the north and south sides "+
        "of the building. They once gave a cross breeze to relieve "+
        "the furnace's heat, but now they are filled with a mixture "+
        "of rocks and mud.\n");

    add_item(({"mixture of rocks and mud", "rocks and mud", 
        "mixture", "rocks", "mud", "rubble"}),
        "The window frames on the north and south walls are filled "+
        "with a jumbled mixture of rocks and mud. It does not look "+
        "like anyone's handiwork so much as the work of nature. "+
        "Perhaps this place was buried by an avalance or something.\n");

    add_item(({"furnace flue", "flue"}), 
        "Fresh air flows from the furnace, indicating that the flue "+
        "is open.\n");

    add_item("ceiling", "It is cracked in places, as if it is "+
        "deteriorating from being under too much pressure. You "+
        "find yourself hoping it does not collapse while you "+
        "are in here.\n"); 

    add_item(({"marble chips", "chips"}),
        "Scattered on the floor of the workshop are chips of "+
        "marble. It looks like someone was sculpting stone.\n");

    add_item(({"wood shavings", "shavings"}),
        "Scattered on the floor of the workshop are shavings "+
        "from some kind of wood. It looks like someone was "+
        "doing some woodworking here.\n");

    add_item(({"ground", "floor"}),
        "It is damaged in places with scratches and dings, but "+
        "oddly clean.  Given that the windows are filled with "+
        "rubble, it makes sense to assume that the room once "+
        "was, too, and at some point it was cleared out.\n");

    add_item(({"workbench", "bench"}),
        "Along the south wall, opposite the racks, is a long "+
        "bench about waist-height.\n");
    
}

public string mylong()
{
    string result=
        "Darkened scorched walls enshroud this stone workshop.  "+
        "The north wall is blanketed with racks full of tools "+
        "and various materials, while a large furnace with a "+
        "pull-out melting pot stretches along the east wall.  "+
        "Large wooden window frames lining either side of the building "+
        "once gave a cross breeze, but now are filled with a mixture "+
        "of rocks and mud.  "+
        "The only air circulation here is from the furnace flue and "+
        "a few visible breaks in the stone from deterioration along "+
        "the ceiling.  "+
        "Marble chips and wood shavings are strewn along the floor near "+
        "a workbench.\n";
        
    if (IS_VAMP(TP) || IS_WIZ(TP))
    {
        result+="You feel there are enough tools and materials to build "+
        "a coffin here.\n";
    }
    return result;
}    



public int filter_valid_material(object ob,string material)
{
    if (living(ob))
    {
        return 0;
    }
    if (member_array(material,ob->query_names())>=0)
    {
        return 1;
    }
    if (member_array(material,ob->query_adj(-1))>=0)
    {
        return 1;
    }
    return 0;
}

public int filter_valid_coffin(object ob,string name)
{
    if (!(ob->query_coffin()))
    {
        return 0;
    }
    if (!ob->query_owner())
    {
        return 1;
    }
    if (ob->query_owner()==name)
    {
        return 1;
    }
    return 0;
}

public void build_coffin(object player,string material,int cost)
{
    object coffin=clone_object(ROOM_DIR+"coffin");
    coffin->set_material(material);
    coffin->set_material_cost(cost);
    coffin->move(TO);
    player->catch_msg("You build "+LANG_ASHORT(coffin)+".\n");
    WATCHERS(player)->catch_msg(QCTNAME(player)+ " finishes building "+
        LANG_ASHORT(coffin)+".\n");
}

public int build(string str)
{
    if (!IS_VAMP(TP) && !IS_WIZ(TP))
    {
        return 0;
    }
    notify_fail("Build coffin with what material?\n");
    if (!str)
    {
        return 0;
    }
    string material;
    if (!parse_command(str,({}),"'coffin' [with] %s",material))
    {
        return 0;
    }
    
    if (!strlen(material))
    {
        return 0;
    }
    
    if (member_array(material,MATERIALS)<0)
    {
        write("You cannot build a coffin with "+material+". If "+
            "available, you may build a coffin from "+
            COMPOSITE_WORDS(sort_array(MATERIALS))+".\n");
        return 1;
    }
    int value=0;
    int weight=0;
    if (material!="wood" && material!="marble")
    {
        object * used=filter(all_inventory(TO),
            &filter_valid_material(,material));
        foreach(object item : used)
        {
            value+=item->query_value();
            weight+=item->query_prop(OBJ_I_WEIGHT);
        }
        if (weight<50000)
        {
            write("You do not have enough "+material+" to build a "+
            "coffin.\n");
            return 1;
        }
        write("You use "+COMPOSITE_DEAD(used)+" for materials to build "+
            "the coffin.\n");
        used->remove_object();
    }
    if (material=="marble")
    {
        value=1000;
    }
    if (material=="wood")
    {
        value=50;
    }

    value=value*max(100,TP->query_vamp_stat())/100;

    write("Having gathered sufficient materials, you start to build a coffin.\n");
    allbb(" starts to build a coffin.\n");
    
    int time=25;
    object paralyze;        
    setuid();
    seteuid(getuid());
    set_alarm(itof(time-1), 0.0, 
        &build_coffin(TP,material,value)); 
    paralyze = clone_object("/std/paralyze");
    paralyze->set_standard_paralyze("building");
    paralyze->set_stop_fun("stop_build");
    paralyze->set_stop_verb("stop");
    paralyze->set_stop_message("You stop building a coffin.\n");
    paralyze->set_remove_time(time);
    paralyze->set_fail_message("You are busy building a "+
     "coffin.  You must 'stop' to do something else.\n");
    paralyze->move(TP,1);    
    
    return 1;
}


public void line_coffin(object player,object coffin,
                string color,string lining,int value)
{
    if (coffin->query_lining() || coffin->query_lining_color())
    {
        return;
    }
    
    coffin->set_lining_color(color);
    coffin->set_lining(lining);
    coffin->set_material_cost(coffin->query_material_cost()+value);

    player->catch_msg("You line "+LANG_THESHORT(coffin)+ " with "+
    color+" "+lining+".\n");
    WATCHERS(player)->catch_msg(QCTNAME(player)+ " lines "+
        LANG_THESHORT(coffin)+" with " +color + " " + lining +".\n");

}


public int line(string str)
{
    if (!IS_VAMP(TP) && !IS_WIZ(TP))
    {
        return 0;
    }
    notify_fail("Line coffin with what color of what material?\n");
    if (!str)
    {
        return 0;
    }
    string color;
    string lining;
    object coffin;
    
    if (!parse_command(str,filter(all_inventory(TO),
        &filter_valid_coffin(,TP->query_real_name())),
        " %o 'with' %w %w",
        coffin,color,lining))
    {
        return 0;
    }

    if (!strlen(lining))
    {
        return 0;
    }

    if (!strlen(color))
    {
        return 0;
    }

    if (member_array(lining,LININGS)<0)
    {
        write("You cannot line your coffin with "+lining+". If "+
            "available, you may line your coffin from "+
            COMPOSITE_WORDS(sort_array(LININGS))+".\n");
        return 1;
    }

    if (member_array(color,LINING_COLORS)<0)
    {
        write("Your coffin lining cannot be "+color+". If "+
            "available, you may use "+
            COMPOSITE_WORDS(sort_array(LINING_COLORS))+" material.\n");
        return 1;
    }
    
    if (coffin->query_lining() || coffin->query_lining_color())
    {
        write("This coffin already has lining.\n");
        return 1;
    }

    int value=0;
    int weight=0;
    object * used=filter(filter(all_inventory(TO),
            &filter_valid_material(,color)),
            &filter_valid_material(,lining));
    foreach(object item : used)
    {
        value+=item->query_value();
        weight+=item->query_prop(OBJ_I_WEIGHT);
    }
    if (weight<4000)
    {
        write("You do not have enough "+color+" "+lining+
        " to build a coffin.\n");
        return 1;
    }
    used->remove_object();

    write("You start to add lining inside the "+coffin->short()+".\n");
    allbb(" starts to add lining inside the "+coffin->short()+".\n");
    
    coffin->remove_prop(CONT_I_CLOSED);
    
    int time=25;
    object paralyze;        
    setuid();
    seteuid(getuid());
    set_alarm(itof(time-1), 0.0, 
        &line_coffin(TP,coffin,color,lining,value)); 
    paralyze = clone_object("/std/paralyze");
    paralyze->set_standard_paralyze("lining");
    paralyze->set_stop_fun("stop_lining");
    paralyze->set_stop_verb("stop");
    paralyze->set_stop_message("You stop lining the coffin.\n");
    paralyze->set_remove_time(time);
    paralyze->set_fail_message("You are busy lining the "+
     "coffin.  You must 'stop' to do something else.\n");
    paralyze->move(TP,1);    

    return 1;

}

public void carve_coffin(object player,object coffin,string carving)
{
    if (!filter_valid_coffin(coffin,player->query_real_name()))
    {
        return;
    }
    if (coffin->query_carving())
    {
        return;
    }
    coffin->set_carving(carving);
    player->catch_msg("You finish your carving on "+
    LANG_THESHORT(coffin)+".\n");
    WATCHERS(player)->catch_msg(QCTNAME(player)+ " finishes carving "+
    "something on "+LANG_THESHORT(coffin)+".\n");
}


public void desc_carving(string desc,object player,object coffin)
{
    if (!strlen(desc) || desc=="quit" || desc=="q" || desc=="~q")
    {
        player->catch_msg("Aborted.\n");
        return;
    }

    if (coffin->query_carving())
    {
        write("This coffin is already carved.\n");
        return;
    }

    write("You start carving into the "+coffin->short()+".\n");
    allbb(" starts to carve into the "+coffin->short()+".\n");
    
    int time=25;
    object paralyze;        
    setuid();
    seteuid(getuid());
    set_alarm(itof(time-1), 0.0, &carve_coffin(TP,coffin,desc)); 
    paralyze = clone_object("/std/paralyze");
    paralyze->set_standard_paralyze("carving");
    paralyze->set_stop_fun("stop_carve");
    paralyze->set_stop_verb("stop");
    paralyze->set_stop_message("You stop carving into the coffin.\n");
    paralyze->set_remove_time(time);
    paralyze->set_fail_message("You are busy carving the "+
     "coffin.  You must 'stop' to do something else.\n");
    paralyze->move(TP,1);    
    return;
}

public int carve(string str)
{
    if (!IS_VAMP(TP) && !IS_WIZ(TP))
    {
        return 0;
    }
    notify_fail("Carve into which coffin?\n");
    if (!str)
    {
        return 0;
    }
    string carving;
    object coffin;
    if (!parse_command(str,filter(all_inventory(TO),
        &filter_valid_coffin(,TP->query_real_name())),
        "'into' [the] %o ",coffin))
    {
        return 0;
    }

    if (coffin->query_carving())
    {
        write("This coffin is already carved.\n");
        return 1;
    }
    
    write("What would you like the carvings to look like?\n] ");
    input_to(&desc_carving(,TP,coffin));
    
    return 1;
}

/*
 * Function name: stop_carve
 * Description:   interrupt carving
 * Arguments:
 * Returns:
 */
varargs int
stop_carve(mixed arg)
{
    if (!objectp(arg))
    {
        mixed *calls = get_all_alarms();
        mixed *args;
        int i;

        for (i = 0; i < sizeof(calls); i++)
        {
            if (calls[i][1] == "carve_coffin")
            {
                args = calls[i][4];
                if (args[0] == TP)
                    remove_alarm(calls[i][0]);
            }
        }
        allbb(" stops carving on the coffin.");
    }

    return 0;
}


/*
 * Function name: stop_lining
 * Description:   interrupt lining
 * Arguments:
 * Returns:
 */
varargs int
stop_lining(mixed arg)
{
    if (!objectp(arg))
    {
        mixed *calls = get_all_alarms();
        mixed *args;
        int i;

        for (i = 0; i < sizeof(calls); i++)
        {
            if (calls[i][1] == "line_coffin")
            {
                args = calls[i][4];
                if (args[0] == TP)
                    remove_alarm(calls[i][0]);
            }
        }
        allbb(" stops lining the coffin.");
    }

    return 0;
}

/*
 * Function name: stop_build
 * Description:   interrupt build
 * Arguments:
 * Returns:
 */
varargs int
stop_build(mixed arg)
{
    if (!objectp(arg))
    {
        mixed *calls = get_all_alarms();
        mixed *args;
        int i;

        for (i = 0; i < sizeof(calls); i++)
        {
            if (calls[i][1] == "build_coffin")
            {
                args = calls[i][4];
                if (args[0] == TP)
                    remove_alarm(calls[i][0]);
            }
        }
        allbb(" stops building a coffin.");
   }
 
    return 0;
}


public void init()
{
    ::init();
    add_action(build,"build");
    add_action(build,"create");
    add_action(line,"line");
    add_action(carve,"carve");
    
    if (TP->query_vampire())
    {
        string location=COFFIN_MANAGER->query_location(TP);
        if (location)
        {
            LOAD_ERR(location);
        }
    }
}

