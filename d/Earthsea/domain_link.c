/* This file is used by the mudlib when the game starts and is shut down
 * DO NOT ALTER THIS FILE UNLESS YOU HAVE BEEN GIVEN PERMISSION.
 * IF YOU HAVE BEEN GIVEN PERMISSION, AND YOU ALTER THIS FILE,
 * BE SURE THAT IT AND THE OBJECTS IT LOADS ARE BUG FREE!
 * ALSO BE SURE THAT YOU OMIT THE .c EXTENSION ON THE FILENAME
 * 
 * Added ship piers to preload 5/20/98--Amelia
 */
#pragma strict_types
#pragma no_clone
#pragma no_shadow

inherit "/std/domain_link";

/*
 * Load items that should be around before players enter the game
 */
nomask void
preload_link()
{
    preload("/d/Earthsea/ships/calia_line/west_pier1");
    preload("/d/Earthsea/ships/ansalon_line/west_pier2");
    preload("/d/Earthsea/ships/avenir_line/east_pier1");
    preload("/d/Earthsea/ships/sparkle_line/east_pier2");
    preload("/d/Earthsea/ships/thwil_line/west_pier3");
    preload("/d/Earthsea/travellers/room/train");
    preload("/d/Earthsea/travellers/room/library");
    preload("/d/Earthsea/guilds/gardeners/master");
    preload("/d/Earthsea/guilds/gardeners/herbdb");
    preload("/d/Earthsea/events/room_tells");
}

public void
delete_player(string name)
{
    setuid();
    seteuid(getuid());
    "/d/Earthsea/guilds/gardeners/master"->erase_deleted_member(name);
    "/d/Earthsea/travellers/log/manager"->remove_council_member(name);
}
