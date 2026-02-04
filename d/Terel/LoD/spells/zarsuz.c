#include <cmdparse.h>
#include <language.h>
#include <ss_types.h>
#include <comb_mag.h>

#include "/d/Terel/include/Terel.h"
#include "/d/Terel/LoD/spells/spells.h"
#include "/d/Terel/LoD/dungeon/quest.h"

#define ADIR (LOD_DIR + "armour/")

#define NAMES ({DQ_OGRE_HEAD, DQ_WOLF_SKIN, DQ_THIEF_HAND})
#define OBJS  ({"ogre_helmet", "wolf_coat", "thief_glove"})

nomask mixed
zarsuz(string str)
{
    object ob, *arr;
    int i, suc, nobj = -1;

    if (!strlen(str))
        return "Zarsuz what?\n";

    if (TP->query_mana() < ZARSUZ_MANA_COST)
        return "You are too tired to attempt this.\n";
    
    if (!parse_command(str, all_inventory(TP), "%i", arr))
        return "Zarsuz what?\n";
        
    arr = NORMAL_ACCESS(arr, 0, 0);
    
    if (sizeof(arr) != 1)
        return "Zarsuz what?\n";
        
    for (i=0; i<sizeof(NAMES); i++)
    {
        nobj = member_array(NAMES[i], arr[0]->query_names());
        if (nobj >= 0)
            break;
    }

    suc = random(TP->query_skill(SS_FORM_TRANSMUTATION));
    suc += random(TP->query_skill(SS_SPELLCRAFT));

    if (suc < random(ZARSUZ_CAST_LIMIT) || nobj == -1) {
        TP->add_mana(-ZARSUZ_MANA_COST/3);
        return "Nothing seems to happen.\n";
    }

    write("Something seems to happen to the " + arr[0]->short() + ".\n");
    i = DURATION(TP->query_stat(SS_INT), TP->query_skill(SS_SPELLCRAFT), 180);
    seteuid(getuid());
    ob = clone_object(ADIR + OBJS[nobj]);
    ob->set_duration(i);
    if (ob->move(TP))
    {
        ob->move(ETP);
        write("You drop " + LANG_ADDART(ob->short()) + ".\n");
        say(QCTNAME(TP) + " drops " + LANG_ADDART(ob->short()) + ".\n");
    }
    TP->add_mana(-ZARSUZ_MANA_COST);
    arr[0]->remove_object();
    return 1;
}
