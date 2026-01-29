/*
 * This objects stores info about possible destinations for dragonsteed
 *
 * In agreemend with Arandir, Liege of Sparkle, and AoD, dragonlanding added
 * for Sparkle on September 16th 2006 by Navarre.
 *
 * Added Palanthas destination. - Mortis 9.2014
 */

#pragma strict_types
#pragma no_clone
#pragma no_shadow

static mapping dests = ([
    "sanction"          : "/d/Ansalon/taman_busuk/sanction/room/city/tower_roof",
    "neraka"            : "/d/Ansalon/taman_busuk/neraka/inner/tower_roof",
    "kalaman"           : "/d/Ansalon/kalaman/city/o4",
    "solamnian plains"  : "/d/Krynn/solamn/splains/room/plain22",
    "flotsam"           : "/d/Ansalon/balifor/flotsam/room/landing",
    "palanthas"         : "/d/Krynn/solamn/palanthas/nobles/ser8",
    "pax tharkas"       : "/d/Krynn/pax/tharkas/court_yard/court_yard2",
    "solace"            : "/d/Krynn/solace/lake/room/lake11",
    "icewall"           : "/d/Krynn/icewall/forest/forest_5",
    "mithas"            : "/d/Ansalon/goodlund/nethosak/forest/room/forest51",
    "sparkle"           : "/d/Genesis/start/human/wild2/peninsula"
    ]);

public string *
query_destinations()
{
    return m_indexes(dests);
}

public string
query_destination_file(string name)
{
    return dests[name];
}

public int
query_open_destination(string name)
{
    dests[name]->load();
    return !!find_object(dests[name]);
}
