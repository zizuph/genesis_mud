/*
 * This master object decides if a rare item may be cloned.
 * It does this by tracking how often attempts are made to clone the item
 * and uses this to calculate the correct drop-percentage
 *
 * - Cotillion 2015-03-08
 */
#pragma strict_types
#pragma no_clone
#pragma resident

#include <std.h>
#include <macros.h>
#include <formulas.h>
#include <stdproperties.h>
#include "/config/sys/local.h"

#define BASE_RESET_INTERVAL       (5400)      /* How often reset_room is called */
#define BASE_RESET_KILL_FREQUENCY (3)         /* Assume unknown npcs are killed this often */
#define BASE_UPTIME               (REGULAR_UPTIME * 3600) /* Uptime Length */

#define ITEMS_LOST_FACTOR         (0.50)      /* With everything recovering and item expiration we assume
                                               * 50% of the items will be from the previous armageddon.
                                               * This is likely where you want to tweak the clone chance. */

#define CLONE_HISTORY             (48)         /* How much clone history to maintain */
#define PURGE_TIME                (86400 * 90) /* Remove entries which have not been cloned for this long */

#define SAVE_FILENAME             ("unique_data")
#define SAVE_INTERVAL             (3600.0)

mapping clones = ([ ]);

void load();
void save();
void purge();


void
create() {
    setuid();
    seteuid(getuid());

    load();
    set_alarm(SAVE_INTERVAL, SAVE_INTERVAL, &save());

    set_alarm(6000.0, 0.0, &purge());
}

void
load() {
    clones = restore_map(MASTER);
}

void
save() {
    save_map(clones, MASTER);
}

static string
fix_filename(string file)
{
    if (wildmatch("*.c", file)) {
        return file[0..-3];
    }
    return file;
}

int
clone_interval(string file) {
    int interval;

    clones[file] = (clones[file] || ({ })) + ({ time() });

    if (sizeof(clones[file]) > 1) {
        interval = (clones[file][-1] - clones[file][0]) / (sizeof(clones[file]) - 1);
        clones[file] = clones[file][-(CLONE_HISTORY)..];
    }

    if (!interval)
        interval = BASE_RESET_INTERVAL * BASE_RESET_KILL_FREQUENCY;
    return interval;
}


/*
 * Get the current drop chance for something
 */
float
query_clone_chance(string file, int num)
{
    int interval;

    if (sizeof(clones[file]) > 1) {
        interval = (clones[file][-1] - clones[file][0]) / (sizeof(clones[file]) - 1);
    }

    if (!interval)
        interval = BASE_RESET_INTERVAL * BASE_RESET_KILL_FREQUENCY;
    int clones = max((REGULAR_UPTIME * 3600) / interval, 1);
    float frequency = itof(num) / itof(clones) * ITEMS_LOST_FACTOR;
    return frequency;
}

/*
 * Calulates how many resets of the npc there is per armageddon and then
 * the percentage chance of dropping the item.
 * file - the file
 * num  - the count
 */
int
may_clone(string file, int num, float chance) {
    int interval, clone; 
    string wiz = "";

    file = fix_filename(file);

    /*
     * This prevents wizards from messing up the clone chance and thinking
     * the system is broken.
     */
    if (this_interactive()->query_wiz_level()) {
        interval = BASE_RESET_INTERVAL * BASE_RESET_KILL_FREQUENCY;
        wiz = this_interactive()->query_real_name();
    } else {
        interval = max(clone_interval(file), 1);
    }

    int clones = max((REGULAR_UPTIME * 3600) / interval, 1);
    float frequency = itof(num) / itof(clones) * ITEMS_LOST_FACTOR;
    
    if (rnd() < frequency)
        clone = 1;

    log_file("clone_unique", sprintf("%s [%d]: %10s %f - %5d %s\n", file, num, 
	(clone ? "CLONED" : "NOT CLONED"), frequency, interval, wiz), 50000);

    return clone;
}

int
reset_interval(string file)
{
    m_delkey(clones, file);
    return 1;
}

/*
 * purge
 *
 * Clear out missing files and items which have not been cloned for 
 * a very long time.
 */
void
purge()
{
    foreach (string file, int *times: clones) {
        if (wildmatch("*.c", file)) {
            clones[fix_filename(file)] = times;
        }

        if (file_size(file + ".c") < 0) {
            log_file("clone_unique", sprintf("%s PURGED File Missing\n", file), 50000);
            m_delkey(clones, file);
            continue;
        }
       
        if (times[-1] < (time() - PURGE_TIME)) {
            log_file("clone_unique", sprintf("%s PURGED Last clone %s\n", file, ctime(times[-1])), 50000);
            m_delkey(clones, file);
            continue;
        }
    }
}
