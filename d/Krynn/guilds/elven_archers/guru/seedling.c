inherit "/std/object";

#include <ss_types.h>
#include <macros.h>
#include "../guild.h"
#include "/d/Ansalon/goodlund/bloodsea/local.h"

#define REFLECTION_ROOM     (BISLAND + "basement01")

static status   gWillowSprout;
static object   gDryadOwner,
                gDryad;

public string
query_seed_short()
{
    if (gWillowSprout)
        return "silvery willow-wood sprout";
    
    return "shimmering seed";
}

public string
query_seed_long()
{
    if (gWillowSprout)
        return "This is the sprout of a silvery willow tree, it is beckoning "
        + "you to pick it up.\n";
    
    return "This is the seedling of a dryad, you may <plant> it in the "
    + "pool of reflection.\n";
}

public mixed
get_willow_sprout()
{
    if (gWillowSprout && this_player() != gDryadOwner)
        return "You are unable to approach the sprout.\n";
    
    return 0;
}


/*
 * Function name: parse_command_id_list
 * Description  : Mask of player_command_id_list() in /std/object.c to make sure
 *                that players cannot use the name of an NPC or player when that
 *                person hasn't been introduced to them.
 * Returns      : string * - the original parse_command_id_list() without the
 *                    lower case name of the person. "Figure" added to list
 *                    of names
 */
public string *
parse_command_id_list()         
{
    string *id_list = ::parse_command_id_list();
    
    if (gWillowSprout)
        return id_list += ({ "sprout" });
   
    return id_list += ({ "seed" });
}

/*
 * Function name: query_adjs
 * Description  : This function returns an array of all adjectives of
 *                this object.
 * Returns      : An array of all adjectives of this object
 *                or false if there are no adjectives.
 */
public string *
query_adjs() 
{
    if (gWillowSprout)
        return ({ "silvery", "wood", "willow", "willow-wood" });
    
    return ({ "shimmering" });
}

/*
 * Function name: query_adj
 * Description  : Gives the adjective(s) of the object.
 * Arguments    : int arg - if true, all adjectives are returns, else only
 *                          the first adjective is returned.
 * Returns      : mixed   - int 0    - if there are no adjectives.
 *                          string   - one adjective if 'arg' is false.
 *                          string * - an array with all adjectives if
 *                                     'arg' is true.
 */
varargs public mixed
query_adj(int arg) 
{
    if (arg)
        return query_adjs();
    else
        return query_adjs()[0];
}

/*
 * Function name: parse_command_adjectiv_id_list
 * Description  : This function is used by the efun parse_command()
 */
public string *
parse_command_adjectiv_id_list() 
{
    if (gWillowSprout)
        return ({ "silvery", "wood", "willow", "willow-wood" });
    
    return ({ "shimmering" });
}

public void 
create_object()
{
    add_name("_archer_guru_quest_seed_");
    set_short("@@query_seed_short@@");
    set_long("@@query_seed_long@@");
    
    add_prop(OBJ_M_NO_DROP, "You can not drop a gift from a goddess.\n");
    add_prop(OBJ_M_NO_GET, "@@get_willow_sprout@@");
}

public object
summon_dryad(object archer)
{
    int    *stats;
    
    setuid();
    seteuid(getuid());
    
    gDryad = clone_object(GURU_DRYAD);
    
    gDryad->set_adj(archer->query_adjs());
    gDryad->set_race_name(archer->query_race_name());
    gDryad->set_gender(archer->query_gender());
    gDryad->set_name(archer->query_race_name());
    stats = allocate(6);
    for (int il = SS_STR; il < SS_RACE; il++)
        stats[il] = archer->query_stat(il);
    gDryad->set_stats(stats);
    gDryad->set_hp(gDryad->query_max_hp());
    gDryad->arm_me();
    gDryad->set_archer(archer);
    gDryad->move(environment(archer), 1);
    
    tell_room(environment(gDryad), 
        "As you plant the shimmering seed at the edge of the pool, it begins "
        + "to grow.\n\nThe seed draws water from the circular pool, rapidly "
        + "growing, deforming, showing signs of corruption.\n\nA humanoid "
        + "begins to take shape, roots and vines covering its body. The "
        + "bark-line skin squirming, changing its appearance to mimic "
        + "yours.\n");
    gDryad->command("kill " + OB_NAME(archer));
    
    return gDryad;
}

public status
plant(string str)
{
    notify_fail("Plant what? the seed?\n");
    if (!strlen(str) || (str != "the seed" && str != "seed"))
        return 0;
    
    if (MASTER_OB(environment(this_player())) != REFLECTION_ROOM)
    {
        notify_fail("This seed can only be planted in the reflection pool.\n");
        return 0;
    }
    
    if (sizeof(filter(all_inventory(environment(this_player())),
        &->id("_archer_guru_quest_seed_"))))
    {
        notify_fail("There is already a seed planted here, you will need to "
        + "wait your turn.\n");
        return 0;
    }
    
    gDryadOwner = this_player();
    
    object dryad = summon_dryad(this_player());
    
    environment(this_player())->set_fetch(1);
    this_object()->move(dryad, 1);
    gWillowSprout = 1;
    return 1;
}

void
init()
{
    ::init();
  
    add_action(plant, "plant");
}

public void
remove_sprout_object()
{
    environment(this_object())->catch_msg("You realize that the sprout would "
    + "make an excellent bow, were it to be strung.\n");
    remove_object();
}
/*
 * Function name: enter_env
 * Description  : When we enter an interactive environment, add a subloc to
 *                indicate that the person is writing something.
 * Arguments    : object to - the object we are entering.
 *                object from - the object we come from.
 */
void
enter_env(object to, object from)
{
    ::enter_env(to, from);
    
    if (query_interactive(to) && gWillowSprout)
    {
        object bow;
        bow = clone_object(DRYAD_BOW);
        bow->unstring_bow();
        bow->move(to, 1);
        set_alarm(0.0, 0.0, &remove_sprout_object());
    }
}
