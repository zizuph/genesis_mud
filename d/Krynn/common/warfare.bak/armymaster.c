/* /d/Krynn/common/warfare/armymaster.c
 *
 * Masterroom of the armies in Krynn/Ansalon
 *
 * This room keeps track of areas, armies and which army occupies which area.
 *
 * Copyright by Hans Breckle (Aridor)
 * 03/99
 *
 * Modification history:
 *
 * Milan 21.2.2000
 * added North and Central Abanasinian plains as well as Solace area
 * removed Abanasinian plains
 * changed add_area() (Ansalon/Krynn wizards with level 17+ can call it now)
 * bugfix in clone_new_npc()
 * added function remove_area()
 * added function clean_up_gRegisteredRooms(). It is called from create_room() and from remove_area()
 * replaced file_size() check from update_conquered_area() by find_object()
 *
 * Milan 23.2.2000
 * clean_up_gRegisteredRooms() now properly updates real number of rooms in areas
 *
 * Boron 18.4.2000
 * Added a peace time until after PEACE_YEAR have been reached currently thats after
 * year 348
 *
 */

#define DEBUG(x)    find_player("milan")->catch_tell(x);find_player("boron")->catch_tell(x);

#include "local.h"
#include CLOCKH
#include RND_MEET
#include TIME_FLOW

#define DESIRED_MONEY_SPENT    350000 /* copper coins per day */
#define PALANTHAS_LIBRARY_BOOK "/d/Krynn/solamn/palan/library/books/v3600"
#define NO_CONQUEST_RESET_TIME 1036800 /* 1 year Krynn time = 12 days real time */
#define TWO_YEARS 2073600 /* For peace */

inherit "/d/Krynn/std/room";

mapping gArea = ([]);
mapping gArmy = ([]);
float exp_scale = 1.4;
int linear_scale = 20; /*144*/
int gStartTime = 0;
string* gQuestsDone = ({});
static string* gRegisteredRooms = ({});

/* prototypes */
/*private*/ int npcs_total_in_area(string area);
/*private*/ string army_in_area(string area);
/*private*/ mixed *army_data_in_area(string area);
/*private*/ mapping clone_data_in_area(string area);
void cleanup_clone_list_in_area(string area);
string *npc_string_list(string army);
public int rooms_in_area(string area);
string *query_areas_of_army(string army);
int calc_price_for_npc(string army, string npc);
string nice_coin_string(int num);
int last_conquer_time(string area);

/* functions */
int
query_peace()
{
    if ( CLOCK->query_year() <= PEACE_YEAR )
    return 1;
    return 0;
}

void
reset_room()
{
}

void
calc_regression()
{
    int i,old = linear_scale,tmp;
    int sum = 1;
    string* idx = m_indexes(gArmy);
    int conquests_ideal = m_sizeof(gArea) * 6;
    /* Ideal is if every area changes posession about <N> (6) times */

    for(i=0;i<sizeof(idx);i++)
      sum += gArmy[idx[i]][6];

    tmp = linear_scale * conquests_ideal / sum;
    linear_scale = tmp;
    if (linear_scale > 288)
      linear_scale = 288;
    if (linear_scale < 20)
      linear_scale = 20;

    linear_scale = 20;
    log_file("armymaster",ctime(time())[4..15] + " Linear_scale was changed from " + old + " to " +
         linear_scale + " (Actually: " + tmp + "), (Conquests: " + sum + ", Ideal: " +
         conquests_ideal +").\n");
}

void
manual_scale_update()
{
    int i;
    string* idx = m_indexes(gArmy);
    string name = TP->query_real_name();
    if (member_array(name,
            "/secure/master"->query_domain_members("Krynn") +
            "/secure/master"->query_domain_members("Ansalon")) < 0 ||
    "/secure/master"->query_wiz_rank(name) < 6)
      return;
    log_file("armymaster","Conquests: ");
    for(i=0;i<sizeof(idx);i++)
      log_file("armymaster",idx[i] + ": " + gArmy[idx[i]][6] + "; ");
    log_file("armymaster","\n");
    calc_regression();
    for(i=0;i<sizeof(idx);i++)
      gArmy[idx[i]][6] = 0;
}

void
log_state(string initiator)
{
    int i;
    string str = "";
    string *areas = TO->query_areas();

    for(i=0;i<sizeof(areas);i++)
      str += sprintf("%25s: %20s\n",areas[i],TO->army_in_area(areas[i]));

    log_file("warfare",
         "\n" + ctime(time())[4..15] + " (" + initiator + ")\n" + str);

    /* We should log this into a book at the library of Palanthas as well! */
    str = "\n" + break_string(GET_TIME_OUTSIDE,78) + "As of this hour (" + ctime(time())[4..23] + "), the Gods have " +
      "decided to turn back\nthe clock. The state of the lands of Ansalon at " +
      "this moment is the following:\n" + str + "\n";
    write_file(PALANTHAS_LIBRARY_BOOK, str);
}

void
automatic_recruit()
{
    FREE_PEOPLE_RECRUIT->reset_room();
}

void
load_default()
{
    string name = TP->query_real_name();

    if (  (member_array(name,
            "/secure/master"->query_domain_members("Krynn") +
            "/secure/master"->query_domain_members("Ansalon")) < 0 ||
    "/secure/master"->query_wiz_rank(name) < 6) &&
    (previous_object() != find_object("/d/Krynn/common/flow/clock")))
    {
    return;
    }


    /* first, record the current state of the areas into a log. */
    log_state(file_name(previous_object()));

    /* then, calculate changes in the costs of the npcs, if necessary */
    calc_regression();

    gQuestsDone = ({});
    gRegisteredRooms = ({});

    /* (["Name of Area":({"Army Name",
     *                    (["Path to Npc left to clone":Number left to clone,...]),
     *                    Size of area (exact number of rooms),
     *                    Number of NPCs cloned (total, for currently occupying army)}),
     *                    Random Table to use for cloning members of the Free People,
     *                    Size of area (approx. number of rooms, used if the exact number doesn't make sense),
     *                    Time of last conquest,
     *                    Average amount of money spent per npc (not used yet),
     *                    ...])
     */

    /* We really need to start with an offset of npcs here. Otherwise, the first to run through all
     * areas can conquer everything and make it near impossible for the other armies to get
     * anything back :-o
     */
    /* NOTE that area names must work with 'the' in front:
     *      - the Solamnian Plains, the Solace Area, the City of Palanthas,
     * NOT: - the Solace
     */
    gArea = ([WAR_AREA_WESTSOL:({"Blue Dragon Army",([]),0,0,"tblsolamnia",85,0,0,}),
          //WAR_AREA_EASTSOL:({"Free People",([]),0,0,"tblsolamnia",396,0,0,}),
          WAR_AREA_ESTWILDE:({"Free People",([]),0,0,"tblestwilde",20,0,0,}),
          //"Throt Area":({"Blue Dragon Army",([]),0,0,"tblthrot",100,0,0,}),
          //"Vingaard Mountains":({"Knights",([]),0,0,"tblvinmount",100,0,0,}),
          //"City of Palanthas":({"Free People",([]),0,0,"tblpalanthas",100,0,0,}),

          WAR_AREA_NORTH_ABANASINIA:({"Blue Dragon Army",([]),0,0,"tblnorthabanasinia",150,0,0,}),
          WAR_AREA_CENTRAL_ABANASINIA:({"Free People",([]),0,0,"tblcentralabanasinia",150,0,0,}),
          //WAR_AREA_ABANASINIAN:({"Free People",([]),0,0,"tblabanasinia",10,0,0,}),
          WAR_AREA_NEWPORT:({"Red Dragon Army",([]),0,0,"tblnewports",100,0,0,}),
          WAR_AREA_SOLACE:({"Free People",([]),0,0,"tblsolace",50,0,0,}),
          //"Gateway Area":({"Red Dragon Army",([]),0,0,"tblgateway",100,0,0,}),
          //"Xak Tsaroth Ruins":({"Black Dragon Army",([]),0,0,"tblxak",100,0,0,}),
          //"Pax Tharkas Fortress":({"Red Dragon Army",([]),0,0,"tblpax",100,0,0,}),
          //"Thorbardin City":({"Free People",([]),0,0,"tblthorbardin",100,0,0,}),
          //"Plains of Dergoth":({"Free People",([]),0,0,"tbldergoth",100,0,0,}),
          WAR_AREA_NIGHLUND:({"Free People",([]),0,0,"tblsolamnia",50,0,0,}),
          WAR_AREA_GUARDLUND:({"Knights",([]),0,0,"tblsolamnia",50,0,0,}),
          WAR_AREA_ICEWALL:({"White Dragon Army",([]),0,0,"tblicewall",50,0,0,}),
          WAR_AREA_THROTYL:({"Free People",([]),0,0,"tblsolamnia",50,0,0,}),
          ]);


    /* (["Name of Army":({Funds spent,Basic AlignDumpment,(["Path to NPC":Cost(gold),...]),
     *                    cost factor,last recruit time,recruit interval,number of conquests,...}),...])
     *
     *
     * Cost(gold) will be the max value of equipment for this npc.
     *            This is the minimum this npc can cost.
     * cost factor will start high and be reduced (to a minimum of 2.0 - why is that?)
     *            appropriately (depending on quests, etc.)
     */

    gArmy = (["Knights":({0,1,(["Rose Knight":({"knight/rose",18}),
                "Sword Knight":({"knight/sword",14}),
                "Crown Knight":({"knight/crown",10}),
                "Knight Squire":({"knight/squire",6}),
                "Sentry":({"knight/sentry",8}),
                ]),5.0,0,3600,0,}),
          "Free People":({0,0,(["Free Person":({"free person",5}),
                    ]),2.0,0,1,0,}),
          "Blue Dragon Army":({0,-1,([/*"Priest":({"blue/priest",25}),*/
                      "Officer":({"blue/officer",18}),
                      "Soldier":({"blue/soldier",12}),
                      "Mercenary":({"blue/mercenary",8}),
                      "Recruit":({"blue/recruit",5}),
                      "Aurak":({"blue/aurak",12}),
                      "Sivak":({"blue/sivak",10}),
                      "Bozak":({"blue/bozak",8}),
                      "Kapak":({"blue/kapak",5}),
                      "Baaz":({"blue/baaz",3}),
                      //"Goblin":({"blue/goblin",4}),
                      //"Hobgoblin":({"blue/hobgoblin",8}),
                      ]),4.0,0,600,0,}),
          "Red Dragon Army":({0,-1,([/*"Priest":({"red/priest",25}),*/
                     "Officer":({"red/officer",18}),
                     "Soldier":({"red/soldier",12}),
                     "Mercenary":({"red/mercenary",10}),
                     "Recruit":({"red/recruit",12}),
                     "Aurak":({"red/aurak",12}),
                     "Sivak":({"red/sivak",10}),
                     "Bozak":({"red/bozak",8}),
                     "Kapak":({"red/kapak",5}),
                     "Baaz":({"red/baaz",3}),
                     //"Goblin":({"red/goblin",4}),
                     //"Hobgoblin":({"red/hobgoblin",8}),
                     ]),4.0,0,600,0,}),
          "Green Dragon Army":({0,-1,([/*"Priest":({"green/priest",25}),*/
                       "Mercenary":({"green/mercenary",12}),
                       "Aurak":({"green/aurak",12}),
                       "Sivak":({"green/sivak",10}),
                       "Bozak":({"green/bozak",8}),
                       "Kapak":({"green/kapak",5}),
                       "Baaz":({"green/baaz",3}),
                       //"Goblin":({"green/goblin",4}),
                       //"Hobgoblin":({"green/hobgoblin",8}),
                       ]),4.0,0,600,0,}),
          "White Dragon Army":({0,-1,([/*"Priest":({"white/priest",25}),*/
                       "Mercenary":({"white/mercenary",12}),
                       "Aurak":({"white/aurak",12}),
                       "Sivak":({"white/sivak",10}),
                       "Bozak":({"white/bozak",8}),
                       "Kapak":({"white/kapak",5}),
                       "Baaz":({"white/baaz",3}),
                       //"Goblin":({"white/goblin",4}),
                       //"Hobgoblin":({"white/hobgoblin",8}),
                       ]),4.0,0,600,0,}),
          "Black Dragon Army":({0,-1,([/*"Priest":({"black/priest",25}),*/
                       "Mercenary":({"black/mercenary",12}),
                       "Aurak":({"black/aurak",12}),
                       "Sivak":({"black/sivak",10}),
                       "Bozak":({"black/bozak",8}),
                       "Kapak":({"black/kapak",5}),
                       "Baaz":({"black/baaz",3}),
                       //"Goblin":({"black/goblin",4}),
                       //"Hobgoblin":({"black/hobgoblin",8}),
                       ]),4.0,0,600,0,}),
          ]);

    gStartTime = time();
    set_alarm(5.0,0.0,automatic_recruit);
    save_object(MASTER);
    save_map((["gRegisteredRooms":gRegisteredRooms]),REGISTEREDROOMSAVE);
}

void
reset_warfare_state()
{
    load_default();
}

void
not_enough_action__reset_clock()
{
    INTERRUPT_PERIOD("clock","restart clock");
}

void
clean_up_gRegisteredRooms(int i, string *tmp)
{
    string *areas;
    int j;

    if (i == 0)
    {
        areas = m_indexes(gArea);
        for (j=0; j < sizeof(areas); j++)
        gArea[areas[j]][2] = 0;
    }

    if (i < sizeof(gRegisteredRooms))
    {
        if (!find_object(gRegisteredRooms[i]) ||
            !gArea[(gRegisteredRooms[i])->query_area_name()])
        {
        tmp += ({ gRegisteredRooms[i] });
    }
    else
    {
            gArea[(gRegisteredRooms[i])->query_area_name()][2]++;
    }
    set_alarm(0.01, 0.0, &clean_up_gRegisteredRooms(i+1, tmp));
    }
    else
    {
    gRegisteredRooms -= tmp;
    save_map((["gRegisteredRooms":gRegisteredRooms]),REGISTEREDROOMSAVE);
    }
}

/* returns 0 if failed, 1 otherwise */
int
remove_area(string area)
{
    string name;

    if (member_array(area, m_indexes(gArea)) < 0)
    return 0;

    name = TP->query_real_name();
    if (member_array(name,
            "/secure/master"->query_domain_members("Krynn") +
            "/secure/master"->query_domain_members("Ansalon")) < 0 ||
    "/secure/master"->query_wiz_rank(name) < 6)
      return 0;

    gArea = m_delete(gArea, area);
    save_object(MASTER);
    set_alarm(0.1, 0.0, &clean_up_gRegisteredRooms(0, ({ })) );
    return 1;
}

void
add_area(string area, string army, string table, int rooms)
{
    string name = TP->query_real_name();

    if (!strlen(area))
    return;

    if (member_array(name,
            "/secure/master"->query_domain_members("Krynn") +
            "/secure/master"->query_domain_members("Ansalon")) < 0 ||
    "/secure/master"->query_wiz_rank(name) < 6)
      return;

    gArea += ([area:({army,([]),0,0,table,rooms,})]);
    save_object(MASTER);
}

int
last_conquest_time()
{
    int i,tme;
    int maxx = 0;
    string* allareas = TO->query_areas();

    for(i=0;i<sizeof(allareas);i++)
    {
    tme = last_conquer_time(allareas[i]);
    if (maxx < tme)
      maxx = tme;
    }
    return maxx;
}

void
init_reset_alarm()
{
    int tme;

    if ( CLOCK->query_year() <= PEACE_YEAR + 2 )
    {
        set_alarm(50000.0, 0.0, init_reset_alarm);
    return;
    }

//  tme = ( TWO_YEARS + last_conquest_time() ) - time() + NO_CONQUEST_RESET_TIME;
//  tme = ( TWO_YEARS + last_conquest_time() ) - time();
    tme = last_conquest_time() - time() + NO_CONQUEST_RESET_TIME;

    if (tme < 0)
      tme = 0;
    set_alarm(itof(tme), 0.0, not_enough_action__reset_clock);
}

void
create_room()
{
    set_short("Area and Army master room");
    set_long("This is the area and army master room of Krynn/Ansalon. " +
         "'areas' will give an overview of the current state of the " +
         "lands, 'armies' will show the armies' point of view.\n");

    restore_object(MASTER);
    gRegisteredRooms = restore_map(REGISTEREDROOMSAVE)["gRegisteredRooms"];

    init_reset_alarm();
    set_alarm(0.1, 0.0, &clean_up_gRegisteredRooms(0, ({ })) );
}

void
init()
{
    add_action("areas","areas");
    add_action("armies","armies");
    ::init();
}

int
npcs_still_to_clone(string area)
{
    int j, tmp = 0;
    mixed* army_data;

    cleanup_clone_list_in_area(area);
    army_data = m_values(clone_data_in_area(area));

    for(j=0;j<sizeof(army_data);j++)
      tmp += army_data[j];
    return tmp;
}

int *
minimized_coins(int num)
{
    int *ret = ({0,0,0,0});

    ret[0] = num % 12;
    num = num - ret[0];
    ret[1] = num % 144;
    num = num - ret[1];
    ret[2] = num % 1728;
    ret[3] = num - ret[2];
    ret[1] /= 12;
    ret[2] /= 144;
    ret[3] /= 1728;
    return ret;
}

string
nice_coin_string(int num)
{
    int *mini = minimized_coins(num);

//    return sprintf("%2d Platinum, %2d Gold, %2d Silver and %2d Copper",
//         mini[3], mini[2], mini[1], mini[0]);
    return sprintf("%2dpc, %2dgc, %2dsc, %2dcc",
           mini[3], mini[2], mini[1], mini[0]);
}

int
query_funds(string army)
{
    return restore_map("/d/Krynn/common/warfare/recruit/" + implode(explode(army," "),""))["gFund"];
    return 23490;
}

int
armies(string str)
{
    int i,j,k,price,funds;
    string *armies = m_indexes(gArmy);
    string *areas;
    string *npcs;

    if ("/secure/master"->query_wiz_rank(TP->query_real_name()) < 4)
      return 0;

    write("                                                                   NPC\n");
    write("Army                         Areas                     NPC         Price\n");
    write("--------------------------------------------------------------------------\n");

    for(i=0;i<sizeof(armies);i++)
    {
    funds = query_funds(armies[i]);
    npcs = npc_string_list(armies[i]);
    areas = query_areas_of_army(armies[i]);
//  write(sprintf("%-25s  ",armies[i]));
    write(sprintf("%-20s  ",armies[i]));
//  write(sprintf("%22s: %8dcc (%s)\n","FUNDS",funds,nice_coin_string(funds)));
    write(sprintf("%10s: %8dcc (%s)\n","FUNDS",funds,nice_coin_string(funds)));

    for(j=0;j<sizeof(areas);j++)
    {
        k = npcs_still_to_clone(areas[j]);
//      write(sprintf("%"+(j==0?"49":"49")+"s: (%d guard%s still in reserve)\n",areas[j], k, (k == 1 ? "" : "s")));
        write(sprintf("%40s: (%d guard%s still in reserve)\n",areas[j], k, (k == 1 ? "" : "s")));
        for(k=0;k<sizeof(npcs);k++)
        {
            price = calc_price_for_npc(areas[j],npcs[k]);
//          write(sprintf("%"+(k==0?"60":"60")+"s: %5dcc  (%s)\n",npcs[k], price, nice_coin_string(price)));
            write(sprintf("%50s: %7dcc\n",npcs[k], price));
        }
    }
    write("\n");
    }
    return 1;
}


int
areas(string str)
{
    int i,tmp;
    string* areas = m_indexes(gArea);

    if ("/secure/master"->query_wiz_rank(TP->query_real_name()) < 4)
      return 0;

    write("                                                       NPCs  NPCs\n");
    write("Area                         Occupant                  left  killed Rooms\n");
    write("--------------------------------------------------------------------------\n");
    for(i=0;i<sizeof(areas);i++)
    {
    tmp = npcs_still_to_clone(areas[i]);
    write(sprintf("%-28s %-20s    %5d  %5d  %5d\n",
              areas[i],army_in_area(areas[i]),
              tmp,npcs_total_in_area(areas[i]),
              rooms_in_area(areas[i])));
    }
    return 1;
}

int
army_alignment(string army)
{
    return gArmy[army][1];
}

void
add_npc(string army, string npc, string path, int cost)
{
    gArmy[army][2] += ([npc:({path,cost})]);
    save_object(MASTER);
}

void
remove_npc(string army, string npc)
{
    gArmy[army][2] = m_delete(gArmy[army][2], npc);
    save_object(MASTER);
}

void
set_price_factor(string army, float factor)
{
    gArmy[army][3] = factor;
    save_object(MASTER);
}

float
query_price_factor(string army)
{
    return gArmy[army][3];
}

void
modify_price_factor(string army, float factor)
{
    gArmy[army][3] *= factor;
    save_object(MASTER);
}


/*private*/ string
army_in_area(string area)
{
    if (!area)
    return 0;
    if (gArea[area])
      return gArea[area][0];
    log_file("armymaster",ctime(time())[4..15] +
         sprintf(" Error in army_in_area: %s (%s)\n", file_name(previous_object()), area));
    return 0;
}

/*private*/ mixed *
army_data_in_area(string area)
{
    return gArmy[army_in_area(area)];
}

/*private*/ mapping
clone_data_in_area(string area)
{
    if (gArea[area])
      return gArea[area][1];
    log_file("armymaster",ctime(time())[4..15] + " Error in clone_data_in_area: " + file_name(previous_object()) + "\n");
    return 0;
}

/*private*/ int
npcs_total_in_area(string area)
{
    if (gArea[area])
      return gArea[area][3];
    log_file("armymaster",ctime(time())[4..15] + " Error in npcs_total_in_area: " + file_name(previous_object()) + "\n");
    return 0;
}

void
add_total_npc(string area, string npc)
{
    if (gArea[area])
      gArea[area][3]++;
    else
      log_file("armymaster",ctime(time())[4..15] + " Error in add_total_npc: " + file_name(previous_object()) + "\n");
}

string
rnd_table_of_area(string area)
{
    if (gArea[area])
      return gArea[area][4];
    else
      log_file("armymaster",ctime(time())[4..15] + " Error in rnd_table_of_area: " + file_name(previous_object()) + "\n");
}


/*private*/ mapping
npc_list(string army)
{
    if (gArmy[army])
      return gArmy[army][2];
    else
      log_file("armymaster",ctime(time())[4..15] + " Error in npc_list: " + file_name(previous_object()) + "\n");
}

/*private*/ string
npc_path(string army, string npc)
{
    if (gArmy[army])
      return gArmy[army][2][npc][0];
    else
      log_file("armymaster",ctime(time())[4..15] + " Error in npc_path: " + file_name(previous_object()) + "\n");
}

/*private*/ string
npc_cost(string army, string npc)
{
    if (gArmy[army])
      return gArmy[army][2][npc][1];
    else
      log_file("armymaster",ctime(time())[4..15] + " Error in npc_cost: " + file_name(previous_object()) + "\n");
}

void
inc_raised_funds(string army, int price)
{
    gArmy[army][0] += price;
}


public int
rooms_in_area(string area)
{
    if (!gArea[area])
      return 0;
    if (gArea[area][5] / 2 > gArea[area][2])
      return gArea[area][5];
    else
      return gArea[area][2];
}

int
last_conquer_time(string area)
{
    if (sizeof(gArea[area]) < 7)
      gArea[area] += ({ 0 });
    return gArea[area][6];
}


public void
register_room(string area)
{
    string fname = file_name(previous_object());

    if (!gArea[area])
    {
    log_file("armymaster",ctime(time())[4..15] + " Error in register_room: " +
         file_name(previous_object()) + "\n");
    return;
    }
    if (member_array(fname, gRegisteredRooms) >= 0)
      return;

    gRegisteredRooms += ({ fname });
    gArea[area][2]++;
    save_object(MASTER);
    save_map((["gRegisteredRooms":gRegisteredRooms]),REGISTEREDROOMSAVE);
}


/*private*/ void
cleanup_clone_list_in_area(string area)
{
    mapping npcs_to_clone;
    string* npcs;
    int i;

    if (!gArea[area])
    {
    log_file("armymaster",
         ctime(time())[4..15] + " Error in cleanup_clone_list_in_area: " +
         file_name(previous_object()) + ". Area: " + area + "\n");
    return;
    }
    npcs_to_clone = gArea[area][1];
    if (!npcs_to_clone ||
    !m_sizeof(npcs_to_clone))
    {
    /*log_file("armymaster",
         ctime(time())[4..15] + " Error in cleanup_clone_list_in_area: " +
         file_name(previous_object()) + " (" + area + ")\n");*/
    /* not an error, just no npcs left to clone because none were bought! */
    return;
    }

    npcs = m_indexes(npcs_to_clone);
    for(i=0;i<sizeof(npcs);i++)
      if (npcs_to_clone[npcs[i]] <= 0)
    npcs_to_clone = m_delete(npcs_to_clone, npcs[i]);

    gArea[area][1] = npcs_to_clone;
    save_object(MASTER);
}


/*private*/ int
can_conquer_area(string area, string newarmy)
{
    cleanup_clone_list_in_area(area);

    if (army_in_area(area) == newarmy)
    {
    notify_fail("Your army is already occupying this area!\n");
    return 0;
    }
    /* We require 30 minutes between two conquests of the same area */
    if (last_conquer_time(area) + 72000 > time())
    {
    notify_fail("There are already reinforcements on the way. You are " +
            "unable to conquer the "+area+".\n");
    return 0;
    }

    if (m_sizeof(clone_data_in_area(area)) > 0)
    {
    notify_fail("The "+area+" doesn't seem to be completely cleared of enemies " +
            "yet, or there are still reinforcements on the way. You " +
            "are unable to conquer the territory.\n");
    return 0;
    }

    return 1;
}

int
price_for_npc(string army, string npc)
{
    mixed *nums = gArmy[army][2][npc];
    if (nums && sizeof(nums))
      return ftoi(itof(nums[1])*gArmy[army][3]);
    return 0;
}

int
query_linear_scale()
{
    return linear_scale;
}

void
set_linear_scale(int num)
{
    string name = TP->query_real_name();
    if (member_array(name,
            "/secure/master"->query_domain_members("Krynn") +
            "/secure/master"->query_domain_members("Ansalon")) < 0 ||
    "/secure/master"->query_wiz_rank(name) < 6)
      return;
    linear_scale = num;
}


int
calc_price_for_npc(string area, string npc)
{
    int price = price_for_npc(army_in_area(area),npc);
    int num = max(1, npcs_still_to_clone(area) +
             npcs_total_in_area(area));
    float p = itof(price)*pow(itof(num),exp_scale)/itof(num);

    return ftoi(p)*linear_scale;
}


/* Base function (private) until here, now follow the 'real' (public)
 * access functions.
 */

/* notest = -1: remove npc from recruit list
 *           0: test if npc is in recruit list (used to calculate price)
 *           1: add npc to recruit list
 *
 * returns: notest!=0: <num> of npcs in the list
 *                     Errors: -1 no such npc
 *                             -2 npc balance off - average money spent is too high
 *                             -3 npc balance off - average money spent is too low
 *          notest==0: <num> price to pay (in cc) for the npc.
 */
varargs int
recruit_npc(string area, string npc, int notest=0)
{
    int tmp;
    int price = calc_price_for_npc(area, npc);
    mapping m;

    if (member_array(npc, npc_string_list(army_in_area(area))) < 0)
      return -1;

    if (notest < -1 || notest > 1)
      notest = 0;
    cleanup_clone_list_in_area(area);
    m = clone_data_in_area(area);
    if (!m || !mappingp(m))
      return -1;
    tmp = (m[npc] += notest);
    save_object(MASTER);
    if (notest == 1)
      inc_raised_funds(army_in_area(area), price);
    if (notest)
      return tmp;
    return price;
}


object
clone_new_npc(string area)
{
    mapping npcs_to_clone;
    string* npcs;
    string npc,path;
    object ob;

    cleanup_clone_list_in_area(area);

    npcs_to_clone = clone_data_in_area(area);

    if (npcs_to_clone && mappingp(npcs_to_clone) &&
    m_sizeof(npcs_to_clone))
    {
    npcs = m_indexes(npcs_to_clone);
    npc = npcs[random(sizeof(npcs))];
    path = npc_path(army_in_area(area),npc);
    if (path == "free person")
      path = GET_RANDOM_NAME(rnd_table_of_area(area));
    if (!strlen(path)) // this was  necessary to prevent errors
        return 0;
    if (path[0..0] != "/")
      path = BASEPATH + path;
    ob = clone_object(path);
    ob->set_belongs_to_army(npc);
    save_object(MASTER);
    return ob;
    }
    return 0;
}


void
npc_killed(string area, mixed npc)
{
    string *npcs;

    if ( query_peace() )
    return;
    if (!area || !stringp(area) || !npc)
    return;

    if (!stringp(npc))
    {
    npcs = m_indexes(clone_data_in_area(area));
    npc = npcs[random(sizeof(npcs))];
    }
    if (recruit_npc(area,npc,-1))
      add_total_npc(area,npc);
    save_object(MASTER);
}


void
update_conquered_area(int i, string area, string newarmy, string oldarmy)
{
    if (i < sizeof(gRegisteredRooms))
    {
    // there are rooms that do not have file but may be in memory
    // and also why load in rooms that are not loaded?
    // if (file_size(gRegisteredRooms[i]) > -1)
    if (find_object(gRegisteredRooms[i]))
      (gRegisteredRooms[i])->conquer_update(area,newarmy,oldarmy);
    set_alarm(0.01,0.0,&update_conquered_area(i+1,area,newarmy,oldarmy));
    }
}

void
reward_warfare_conquest(object who, string area, string newarmy, string oldarmy)
{
    who->reward_warfare_conquest(area,newarmy,oldarmy);
}


varargs int
conquer_area(string area, string newarmy, int silent=0)
{
    int i,size;
    function f;
    string room;
    string mystr,youstr;
    string oldarmy = army_in_area(area);

    if ( query_peace() )
    {
        notify_fail("\nConquer? - But you aren't at war!\n\n");
        return 0;
    }

    /* notify_fail will be set in can_conquer_area */
    if (!can_conquer_area(area, newarmy))
      return 0;

    if (!silent)
    {
    switch(newarmy)
    {
    case "Free People": mystr = "After cleaning the "+area+" of any enemies, " +
      "you conquer the territory and declare it free once again!";
        youstr = " declares the territory free once again!";
        break;
    case "Knights": mystr = "After cleaning the "+area+" of any aggressors, you " +
      "conquer the territory and declare it secured by the Knights of Solamnia!";
        youstr = " declares the territory secured by the Knights of Solamnia!";
        break;
    default: mystr = "After cleaning the "+area+" of any enemies, you conquer " +
      "the territory and declare it property of the " + newarmy + "!";
        youstr = " marks the territory as property of the " + newarmy + "!";
        break;
    }
    write(mystr +" Recruit guards to make sure the area remains secured.\n");
    say(QCTNAME(TP) + youstr + "\n");
    }

    gArea[area] = ({newarmy,([]),gArea[area][2],0,gArea[area][4],gArea[area][5],time(),});
    gArmy[newarmy][6]++;
    save_object(MASTER);

    set_alarm(0.0,0.0,&reward_warfare_conquest(TP,area,newarmy,oldarmy));

    if (silent)
    {
    log_file("warfare",
         sprintf("\n%s: %s (%s) conquers %s from %s",
             ctime(time())[4..15], "FreePeopleRecruit", newarmy, area, oldarmy));
    find_player("aridor")->catch_msg(sprintf("%s: %s (%s) conquers %s from %s\n",
                         ctime(time())[4..15], "FreePeopleRecruit", newarmy, area, oldarmy));
    }
    else
    {
    log_file("warfare",
         sprintf("\n%s: %s (%s) conquers %s from %s",
             ctime(time())[4..15], TP->query_name(), newarmy, area, oldarmy));
    find_player("aridor")->catch_msg(sprintf("%s: %s (%s) conquers %s from %s\n",
                         ctime(time())[4..15], TP->query_name(), newarmy, area, oldarmy));
    }
    /* Tell all rooms that some area has been conquered in case there is
     * something to do.
     * This produces quite some processor load, so it better not happen
     * too frequently!
     */
    set_alarm(0.1,0.0,&update_conquered_area(0,area,newarmy,oldarmy));

    return 1;
}

string
army_of_player(object player)
{
    string occ = player->query_guild_name_occ();
    string div = player->query_dragonarmy_division();
    /*string race = player->query_guild_name_race();*/
    string army = "Free People";

    switch(occ)
    {
    case "Solamnian Knights":    army = "Knights";
    break;
    }
    switch(div)
    {
    case "red": army = "Red Dragon Army";
    break;
    case "blue": army = "Blue Dragon Army";
    break;
    case "black": army = "Black Dragon Army";
    break;
    case "white": army = "White Dragon Army";
    break;
    case "green": army = "Green Dragon Army";
    break;
    }

    return army;
}

int
allowed_to_conquer(object player, string army)
{
    if (army == "Free People")
    {
    if (!player)
      return 1;
    if (player->query_guild_name_occ() ==
        "Dwarven Warriors of the Neidar Clan")
      return 1;
    return 0;
    }
    return 1;
}

int
conquer(object player, string area)
{
    string army = army_of_player(player);

    if (!allowed_to_conquer(player, army))
    {
    NF("What?\n");
    return 0;
    }
    return conquer_area(area, army);
}

string *
npc_string_list(string army)
{
    return m_indexes(npc_list(army));
}


mixed *
query_army(string army)
{
    return gArmy[army];
}

mixed *
query_area(string area)
{
    return gArea[area];
}

string *
query_armies()
{
    return m_indexes(gArmy);
}

string *
query_areas()
{
    return m_indexes(gArea);
}

int
correct_army(mixed area, string army)
{
    return army == army_in_area(area);
}

string *
query_areas_of_army(string army)
{
    return filter(query_areas(), &correct_army(,army));
}


varargs void
done_quest(string quest, string armyofsolver = 0)
{
    string questname = quest;

    if (member_array(quest,gQuestsDone) >= 0)
      return;

    switch(quest)
    {
    case "dragonlance": modify_price_factor("Knights", 0.7);
    break;
    case "black_dragon_good": modify_price_factor("Knights", 0.6);
    modify_price_factor("Black Dragon Army", 1.1);
    questname = "black_dragon";
    break;
    case "black_dragon_evil": modify_price_factor("Red Dragon Army", 0.7);
    modify_price_factor("Black Dragon Army", 1.1);
    questname = "black_dragon";
    break;
    case "prisoner_quest": modify_price_factor(armyofsolver, 0.9);
    modify_price_factor("Free People", 0.7);
        /* =0.63 if solver is of the Free People */
    break;
    case "drac_prisoner": modify_price_factor("Knights", 0.95);
    break;
    case "help_refugees": modify_price_factor("Free People", 0.85);
    break;
    default: return;
    }

    gQuestsDone += ({ questname });
    save_object(MASTER);
}

