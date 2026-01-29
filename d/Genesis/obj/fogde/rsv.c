/*
 * Copyright notice, please read.
 *
 * Copyright Chalmers Datorf|rening, 1992
 *
 * You are welcome to read this file for information & education purposes.
 * However, you are expressly forbidden to copy this code for use in any
 * other mud. This code is part of Genesis and we want Genesis to remain
 * unique. You must invent your own world on your own mud.
 *
 */

void start_fogde();
static object fogde;

mapping suckers;

void
create()
{
    start_fogde();
    suckers =([]);
}

void
reset()
{
    start_fogde();
}

void
start_fogde()
{
    string *dest;
    object kista;

    setuid();
    seteuid(getuid());

    dest = ({
	"/d/Genesis/start/human/town/tower",
	"/d/Genesis/start/hobbit/v/guild",
	"/d/Genesis/start/goblin/caverns/quarters",
	"/d/Genesis/start/elf/room/vill_board"
	});

    if (objectp(fogde))
    {
	fogde->move(dest[random(sizeof(dest))], 0);
	return;
    }

    fogde = clone_object("/d/Genesis/obj/fogde/fogden");
    kista = clone_object("/d/Genesis/obj/fogde/kassakista");

    kista->move(fogde, 0);
    fogde->move(dest[random(sizeof(dest))], 0);

    fogde->command("wield box");
    fogde->command("smile");
    fogde->command("say Ready for action!\n");
}

public void
add_victim(string who, object money)
{
    int *all;

    all = suckers[who];
    if (!sizeof(all))
    {
	all = ({ 0, 0, 0, 0 });
	suckers += ([ who:all ]);
    }

    switch(money->query_coin_type())
    {
    case "copper":
	all[0] += money->num_heap();
	break;
	
    case "silver":
	all[1] += money->num_heap();
	break;
	
    case "gold":
	all[2] += money->num_heap();
	break;
	
    case "platinum":
	all[3] += money->num_heap();
	break;
	
    default:
	/* Strange coin indeed */
	break;
    }
    suckers[who] = all;
}

public mapping
query_victims()
{
    return suckers;
}
