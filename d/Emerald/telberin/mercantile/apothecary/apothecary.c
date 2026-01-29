inherit "/d/Emerald/std/elf";

#include "../../defs.h"
#include <money.h>
#include <macros.h>
#include <files.h>

#define MED_DIR (TELBERIN_MERCANTILE_DIR + "apothecary/medications/")
#define MED_PRICE(med)    (med->query_prop((IS_HEAP_OBJECT(med) ? \
                          HEAP_I_UNIT_VALUE : OBJ_I_VALUE)) * 120 / 100)

public mapping med_map = ([]);

public void
load_medications()
{
    string *meds;
    string med_file;
    int i;
    object med;
  
    setuid();
    seteuid(getuid());
    meds = get_dir(MED_DIR);

    for (i = 0; i < sizeof(meds); i++)
    {
        med_file = MED_DIR + meds[i];
        LOAD_ERR(med_file);
        if (!(med = find_object(med_file)))
	{
  	    continue;
	}

        if (!med->query_medication())
	{
	    continue;
	}

        med_map[med->query_medication_name()] = ({ med_file, MED_PRICE(med) });
    }
}

public void
create_elf()
{
    load_medications();
}

public int
list_medications(string str)
{
    int *price;
    string price_str, *meds;
    int i, j;

    meds = m_indices(med_map);

    if (!sizeof(meds))
    {
        write("The apothecary has nothing available at the moment.\n");
        return 1;
    }

    for (i = 0; i <sizeof(meds); i++)
    {
        price = MONEY_SPLIT(med_map[meds[i]][1]);
        price_str = "";
        for (j = sizeof(MONEY_TYPES) - 1; j >= 0; j--)
	{
	    if (price[j] == 0)
	    {
	        continue;
	    }

  	    price_str += price[j] + " " + FCHAR(MONEY_TYPES[j]) + "c ";
        }

        write(sprintf("%-30s %25s\n", meds[i], price_str));
    }

    return 1;
}

public int
buy_medication(string str)
{
    mixed *med_data;
    object med;

    med_data = med_map[str];
    if (!med_data)
    {
        return 0;
    }

    if (!MONEY_ADD(this_player(), -med_data[1]))
    {
        return 1;
    }

    setuid();
    seteuid(getuid());
    med = clone_object(med_data[0]);
    med->move(this_player(), 1);
    
    write("Ok.\n");
    return 1;
}

public void
init_living()
{
    ::init_living();
    add_action(list_medications, "list");
    add_action(buy_medication, "buy");
}
