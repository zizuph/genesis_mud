/*
 *  Inherit this item as a basic bait type.
 *
 *  Arman, March 2021
 */
#include <composite.h>
#include <files.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <wa_types.h>
#include "/d/Krynn/common/defs.h"

inherit "/d/Krynn/common/fishing/fishing_bait";
inherit "/lib/keep";

mixed * fish_value = ({ });
int vol, wgt, val, bait_val, bait, challenge, mod_val;
string name, short, long, * adj, area;

// Contains the list of catchable fish types
#include "/d/Krynn/common/fishing/fish_file.h";

#define FILLET "/d/Krynn/common/fishing/fish_fillet"

#define FISH_DEBUG(x)  find_player("arman")->catch_msg("[Fish] " + x + "\n")


public void
set_fish_value(string area, int bait, int challenge)
{
    fish_value = ({ area, bait, challenge });
    return;
}

public mixed *
query_fish_value()
{
    return fish_value;
}

public void
generate_fish()
{
    // fish value based on area fished in, the bait
    // value used to catch the fish, and how challenging
    // the area is (usually based on rough sea ratings)

    if(!sizeof(fish_value))
        fish_value = ({ "default", 1, 0 });

    area = fish_value[0];
    bait = fish_value[1];
    challenge = fish_value[2];

    // FISH_DEBUG("bait value: " +bait+ ", challenge: " +challenge+ 
    //    ", area: " +area);

    switch(area)
    {
        // The "deep_sea_fishing" area type SHOULD NOT
        // be set for a room. It is to distinguish big
        // game fish that can only be found with random
        // spawning objects in waterways, such as
        // /d/Krynn/south_courrain/living/deep_sea_fishing_obj.c

        case "deep_sea_fishing":
            switch(bait)
            {
                case 0..4:
                    switch(random(100))
                    {
                        case 0..74:
                            blue_herring();
                        break;
                        case 75..99:
                            king_salmon();
                        break;
                        default:
                            blue_herring();
                        break;
                    }
                break;
                case 5..15:
                    switch(random(100))
                    {
                        case 0..10:
                            blue_herring();
                        break;
                        case 11..30:
                            king_salmon();
                        break;
                        case 31..50:
                            striped_sailfish();
                        break;
                        case 51..70:
                            yellowfin_tuna();
                        break;
                        case 71..85:
                            black_swordfish();
                        break;
                        case 86..95:
                            black_marlin();
                        break;
                        default:
                            blue_marlin();
                        break;
                    }
                break;
                default:
                    switch(random(100))
                    {
                        case 0..1:
                            blue_herring();
                        break;
                        case 2..20:
                            striped_sailfish();
                        break;
                        case 21..40:
                            yellowfin_tuna();
                        break;
                        case 41..60:
                            black_swordfish();
                        break;
                        case 61..80:
                            black_marlin();
                        break;
                        default:
                            blue_marlin();
                        break;
                    }
                break;
            }
            break;
        case "balifor":
            switch(bait)
            {
                case 0..1:
                    switch(random(100))
                    {
                        case 0..15:
                            bait_fish();
                        break;
                        case 16..35:
                            blue_herring();
                        break;
                        case 36..70:
                            silvery_whiting();
                        break;
                        case 71..85:
                            spotted_flathead();
                        break;
                        default:
                            poddy_mullet();
                        break;
                    }
                break;
                default:
                    switch(random(100))
                    {
                        case 0..25:
                            sea_mullet();
                        break;
                        case 26..50:
                            silvery_whiting();
                        break;
                        default:
                            balifor_bonito();
                        break;
                    }
                break;
            }
            break;
        case "blue_bottom_bay":
            switch(bait)
            {
                case 0..1:
                    switch(random(10000))
                    {
                        case 0:
                            golden_fish();
                        break;
                        case 0..1500:
                            spiky_bloatfish();
                        break;
                        case 1501..6500:
                            silvery_whiting();
                        break;
                        case 6501..9500:
                            thread_herring();
                        default:
                            customised_fishing_catch_junk();
                        break;
                    }
                break;
                case 2..5:
                    switch(random(10000))
                    {
                        case 0:
                            golden_fish();
                        break;
                        case 0..500:
                            spiky_bloatfish();
                        break;
                        case 501..1500:
                            silvery_whiting();
                        break;
                        case 1501..3500:
                            thread_herring();
                        break;
                        case 3501..7000:
                            bait_fish();
                        break;
                        case 7001..8500:
                            blue_herring();
                        break;
                        default:
                            poddy_mullet();
                        break;
                    }
                break;
                default:
                    switch(random(1000))
                    {
                        case 0:
                            golden_fish();
                        break;
                        case 1..100:
                            bait_fish();
                        break;
                        case 101..350:
                            thread_herring();
                        break;
                        case 351..700:
                            silvery_whiting();
                        break;
                        case 701..850:
                            blue_herring();
                        break;
                        default:
                            blacktail_dartfish();
                        break;
                    }
                break;
            }
            break;
        case "bloodsea":
            switch(bait)
            {
                case 0..1:
                    switch(random(100))
                    {
                        case 0..15:
                            bait_fish();
                        break;
                        case 16..35:
                            blue_herring();
                        break;
                        case 36..70:
                            silvery_whiting();
                        break;
                        case 71..85:
                            spotted_flathead();
                        break;
                        default:
                            poddy_mullet();
                        break;
                    }
                break;
                default:
                    switch(random(100))
                    {
                        case 0..20:
                            sea_mullet();
                        break;
                        case 21..45:
                            red_snapper();
                        break;
                        case 46..75:
                            king_salmon();
                        break;
                        default:
                            bloodsea_barracuda();
                        break;
                    }
                break;
            }
            break;
        case "crystalmir":
            switch(bait)
            {
                case 0..1:
                    switch(random(100))
                    {
                        case 0..25:
                            bait_fish();
                        break;
                        case 26..50:
                            rainbow_trout();
                        break;
                        case 51..75:
                            freshwater_drum();
                        break;
                        default:
                            redfin_perch();
                        break;
                    } 
                break;
                // Certain bait of quality '4'
                case 4:
                    switch(random(100))
                    {
                        case 0..25:
                            customised_fishing_catch_crystalmir_net();
                        break;
                        case 26..50:
                            silver_bass();
                        break;
                        case 51..75:
                            freshwater_drum();
                        break;
                        default:
                            silver_bass();
                        break;
                    } 
                break;
                default:
                    switch(random(100))
                    {
                        case 0..20:
                            freshwater_drum();
                        break;
                        case 21..40:
                            redfin_perch();
                        break;
                        case 41..85:
                            brown_trout();
                        break;
                        default:
                            blue_eyed_cod();
                        break;
                    }                   
                break;
            }
            break;
        case "courrain":
        case "saltwater":
            switch(bait)
            {
                case 0..1:
                    switch(random(100))
                    {
                        case 0..15:
                            bait_fish();
                        break;
                        case 16..35:
                            blue_herring();
                        break;
                        case 36..70:
                            silvery_whiting();
                        break;
                        case 71..85:
                            spotted_flathead();
                        break;
                        default:
                            poddy_mullet();
                        break;
                    }
                break;
                default:
                    switch(random(100))
                    {
                        case 0..20:
                            sea_mullet();
                        break;
                        case 21..45:
                            silvery_whiting();
                        break;
                        case 46..75:
                            red_snapper();
                        break;
                        case 76..90:
                            king_salmon();
                        break;
                        default:
                            yellowfin_tuna();
                        break;
                    }
                break;
            }
            break;
        case "freshwater":
            switch(bait)
            {
                case 0..1:
                // FISH_DEBUG("0..1 freshwater called");
                    switch(random(100))
                    {
                        case 0..25:
                            bait_fish();
                        break;
                        case 26..50:
                            rainbow_trout();
                        break;
                        case 51..75:
                            freshwater_drum();
                        break;
                        default:
                            redfin_perch();
                        break;
                    } 
                break;
                default:
                // FISH_DEBUG("default freshwater called");
                    switch(random(100))
                    {
                        case 0..20:
                            freshwater_drum();
                        break;
                        case 21..40:
                            redfin_perch();
                        break;
                        case 41..85:
                            brown_trout();
                        break;
                        default:
                            blue_eyed_cod();
                        break;
                    }                   
                break;
            }
            break;
        case "reefcutter_wreck":
            switch(bait)
            {
                case 0..1:
                    switch(random(100))
                    {
                        case 0..15:
                            bait_fish();
                        break;
                        case 16..35:
                            blue_herring();
                        break;
                        case 36..70:
                            silvery_whiting();
                        break;
                        case 71..85:
                            spotted_flathead();
                        break;
                        default:
                            poddy_mullet();
                        break;
                    }
                break;
                case 4:
                    switch(random(100))
                    {
                        case 0..35:
                            blue_herring();
                        break;
                        case 36..50:
                            silvery_whiting();
                        break;
                        case 51..65:
                            spotted_flathead();
                        break;
                        default:
                            customised_fishing_catch_reefcutter_wreck();
                        break;
                    }
                break;
                default:
                    switch(random(100))
                    {
                        case 0..20:
                            sea_mullet();
                        break;
                        case 21..45:
                            silvery_whiting();
                        break;
                        case 46..75:
                            red_snapper();
                        break;
                        case 76..90:
                            king_salmon();
                        break;
                        default:
                            yellowfin_tuna();
                        break;
                    }
                break;
            }
            break;
        case "subterranean":
            switch(random(100))
            {
                case 0..74:
                    blind_cavefish();
                break;
                default:
                    toothy_quipper();
                break;
            }
            break;
        case "alpine_lake":
            switch(bait)
            {
                case 0..1:
                    switch(random(100))
                    {
                        case 0..10:
                            bait_fish();
                        break;
                        case 11..65:
                            rainbow_trout();
                        break;
                        case 66..75:
                            arctic_char();
                        break;
                        default:
                            cutthroat_trout();
                        break;
                    } 
                break;
                default:
                    switch(random(100))
                    {
                        case 0..20:
                            rainbow_trout();
                        break;
                        case 21..65:
                            cutthroat_trout();
                        case 66..95:
                            arctic_char();
                        break;
                        default:
                            alpine_sturgeon();
                        break;
                    }                   
                break;
            }
            break;
        case "default":
        default:
            switch(random(100))
            {
                case 0..60:
                    bait_fish();
                    break;
                default:
                    spiky_bloatfish();
                    break;
            } 
    }

    return;
}

int
query_size_modifier()
{
    float modifier, mod_value;

    // size modifier influenced by:
    //    how challening the conditions are (0 - 100)
    //    the bait used (value 1 - 20)
    modifier = itof(random(150));
    modifier += itof(random(challenge));
    modifier += itof(min(20, bait)) * 5.0;

    // Between 10% and 116% size.
    mod_value = max(0.1, (modifier / 300.0)) * 100.0;

    return ftoi(mod_value);
}

public string
query_fish_short()
{
    if(strlen(short))
        return short;
    else
        return query_short();
}

public void
create_fish()
{ 
    set_bait_value(bait_val);

    if(bait_value)
    {
        add_name("_fishing_bait");
        add_name("bait");
        set_long(long + "@@query_bait_quality_description");
    }
    else
        set_long(long);

    add_name("fish");
    add_name("global_fish_obj");
    add_pname("fishes");
    set_name(name);
    set_short(short);
set_pshort(short + "s");
    add_adj(adj);

    if(short == "Balifor bonito")
    {
        add_name("_balifor_bonito");
    }   

    if(short == "bait fish")
    {
        add_name("baitfish");
    }  

    // % size modifier
    if(!mod_val)
    {
        mod_val = query_size_modifier();

        // Size of fish varies depending on fishing success
        vol = max(1, vol * mod_val / 100);
        wgt = max(1, wgt * mod_val / 100);
        val = max(1, val * mod_val / 100);
    }

    // FISH_DEBUG("Size modifier: " +mod_val+ "%");

    switch(mod_val)
    {
        case 0..35:
            add_adj("small");
            set_short("small " +short);
        break;
        case 36..64:
        break;
        case 65..95:
            add_adj("large");
            set_short("large " +short);
        break;
        case 96..150:
            add_adj("huge");
            set_short("huge " +short);
        break;
        default:
            add_adj("average");
            set_short("average " +short);
    }

    // Food amount in grams.
    set_amount(wgt / 5);

    add_prop(HEAP_I_UNIT_VOLUME, vol);
    add_prop(HEAP_I_UNIT_WEIGHT, wgt);
    add_prop(HEAP_I_UNIT_VALUE, val);

    // Stacking issues with heaps with varying weights and volumes
    string unique_str = "krynn_fish_" + file_name(this_object());

    add_prop(HEAP_S_UNIQUE_ID, unique_str);
}

public void 
create_food()
{
    set_name("fish");
    set_long("Default fish object.\n");	
}

public int
filter_held_knives(object ob)
{
    if (!ob)
    {
        return 0;
    }
    if (!ob->check_weapon())
    {
        return 0;
    }

    int i = ob->query_wt();

    if (i == W_KNIFE)
    {
        return 1;
    }
    
    return 0;
}

/*
 * Function name:        fillet_fish
 * Description  :        Fillets the fish object down to smaller food packets
 * Arguments    :        string str - what the player typed after the verb
 * Returns      :        1 - success, 0 - failure
 */
public int
fillet_fish(string str)
{
    object fish_obj, fillet;
    int eat, fillet_num, size, val;
    string name, short, long, wep_short;
    mixed *weapons; 
    
    if(!strlen(str))
    {
        notify_fail("Fillet what?\n");
        return 0;
    }

    if (!parse_command(str, deep_inventory(this_player()) + 
        deep_inventory(environment(this_player())), "[the] %o", fish_obj))
    {
        notify_fail("Fillet what??\n");
        return 0;
    }
     
    if (!fish_obj->id("global_fish_obj")) 
    {
        notify_fail("You cannot fillet " +fish_obj->short()+ 
            ".\n");
        return 0;
    }

    weapons = this_player()->query_weapon(-1);

    if(!sizeof(weapons))
    {
        notify_fail("You need to be wielding a knife to fillet " +
            fish_obj->short()+ ".\n");
        return 0;
    }

    weapons = filter(weapons, filter_held_knives);

    if(!sizeof(weapons))
    {
        notify_fail("You need to be wielding a knife to fillet " +
            fish_obj->short()+ ".\n");
        return 0;
    }

    wep_short = weapons[0]->short();
  
    eat = fish_obj->query_amount();

    if(eat < 100)
    {
        notify_fail(capitalize(fish_obj->short())+ 
            " is too small for you to fillet enough meat from!\n");
        return 0;
    }

    if(eat < 400)
    {
        fillet_num = eat / 100;
        size = 100;
        val = min(1, fish_obj->query_prop(HEAP_I_UNIT_VALUE) / fillet_num);
    }
    else
    {
        fillet_num = eat / 400;
        size = 400;
        val = min(1, fish_obj->query_prop(HEAP_I_UNIT_VALUE) / fillet_num);
    }

    name = fish_obj->query_name();
    short = fish_obj->query_fish_short() + " fillet";
    long = "This is the fillet of " +
        LANG_ADDART(fish_obj->query_fish_short())+ ".\n";

    setuid();
    seteuid(getuid());

    fillet = clone_object(FILLET);
    fillet->set_fillet_attributes(size, size, val, name, short, long);
    fillet->create_fillet();
    fillet->set_heap_size(fillet_num);
    fillet->move(this_player(), 1);

    if(fillet_num > 1)
        write("You cut " +fillet_num+ " fillets from " +fish_obj->short()+ 
            " with your " +wep_short+ ".\n");
    else
        write("You cut a fillet from " +fish_obj->short()+ 
            " with your " +wep_short+ ".\n");
    say(QCTNAME(this_player()) + " fillets " +fish_obj->short()+ 
        " with " +HIS(this_player())+ " " +wep_short+ ".\n");

    fish_obj->remove_object();
     
    return 1;
}

/*
 * Function name:        init
 * Description  :        add some actions to the player
 */
public void
init()
{
    ::init();

    add_action(fillet_fish, "fillet");

} /* init */

/*
 * Function name: query_recover
 * Description  : This function is called to see whether this object may
 *                recover. It will only function for food that has a
 *                real file rather than being cloned from /std/food.c
 *                since only the amount of food on the heap is saved.
 */
public string
query_recover()
{
    string file = MASTER;
    /* Don't recover bare /std/drinks since we only recover the amount of
     * drinks and no descriptions.
     */
    if (file == FOOD_OBJECT)
    {
        return 0;
    }

    return file + ":heap#" + num_heap() + "#" + vol + "&&" +
        wgt + "&&" + val + "&&" + bait_val + "&&" + name + "&&" +
        short + "&&" + long + "&&" + adj[0] + "&&" + mod_val;
}

/*
 * Function name: init_recover
 * Description  : This function is called when the food recovers.
 * Arguments    : string str - the recover argument.
 */
public void
init_recover(string str)
{
    string foobar;
    int    num;

    if (sscanf(str, "%sheap#%d#%s", foobar, num, foobar) == 3)
    {
        set_heap_size(num);
    }

    string *a = explode(foobar,"&&");
    vol = atoi(a[0]);
    wgt = atoi(a[1]);
    val = atoi(a[2]);
    bait_val = atoi(a[3]);
    name = a[4];
    short = a[5];
    long = a[6];
    adj = ({ a[7] });
    mod_val = atoi(a[8]);

    if(sizeof(a) > 1)
        create_fish();
}
