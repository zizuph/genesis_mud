#define CARAVAN "/d/Kalad/common/caravan/"
#define PASS "/d/Kalad/common/wild/pass/"

#define RAID "/d/Kalad/common/wild/pass/raid_base/"
#define ROOM (RAID + "room/")
#define NPC  (RAID + "npc/")
#define LOG  (RAID + "log/")

#define RAID_GOBLIN_LEFTOVER "_kalad_raid_goblin_leftover"
#define RAID_HUMAN_LEFTOVER "_kalad_raid_human_leftover"

#define RAID_GOBLIN_REWARD "_kalad_raid_goblin_reward"
#define RAID_HUMAN_REWARD "_kalad_raid_human_reward"

#define SCROLLING_LOG(file, entry)   ((file_size(file) > 10000) ? \
   (rm(file) && write_file(file, ctime(time()) + ": " + entry + "\n")) :\
   (write_file(file, ctime(time()) + ": " + entry + "\n")))
