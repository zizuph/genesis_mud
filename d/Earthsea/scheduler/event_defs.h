// Basic event history properties (array indexes)

#define H_TYPE 0
#define H_DOMAIN 1
#define H_START 2
#define H_WINNER 3

// Basic event properties (array indexes)

#define E_TYPE 0
#define E_DOMAIN 1
#define E_START 2
#define E_END 3
#define E_STATUS 4
#define E_CREATOR 5
#define E_RW_TYPE 6
#define E_RW_AMNT 7
#define E_DESC 8
#define E_ANNOUNCE 9
#define E_ANNOUNCE_MINS 10
#define E_PROPS 11

#define ET_HANDLER 0
#define ET_PROPS 1

// Basic event properties (prop names)

#define P_TYPE "type"
#define P_DOMAIN "domain"
#define P_START "start"
#define P_END "end"
#define P_STATUS "status"
#define P_CREATOR "creator"
#define P_RW_TYPE "reward_type"
#define P_RW_AMNT "reward_amount"
#define P_DESC "description"
#define P_ANNOUNCE "announcement"
#define P_ANNOUNCE_MINS "announcement_mins"

#define P_DATE "date"

// Reward types for winning on event

#define RW_COINS 0
#define RW_QXP 1
#define RW_CXP 2
#define RW_GXP 3
#define RW_ITEM 4
#define RW_NONE 5

#define RW_TYPES ({"Coins","Quest XP","Combat XP","General XP",\
  "Item","None"})
#define RW_DESC  ({"a nice heap of coins",\
  "a little bit of quest experience","some combat experience",\
  "a nice amount of general experience","a marvelous item",\
  "no reward" })

#define PT_INT "int"
#define PT_STRING "string"
#define PT_MEMO "memo"
#define PT_ARRAY "array"
#define PT_DATETIME "datetime"
#define PT_BOOLEAN "boolean"

#define ST_SCHEDULING "scheduling"
#define ST_PENDING "pending"
#define ST_ALTERING "altering"
#define ST_RUNNING "running"
#define ST_FINISHED "finished"

#define W_WINNER 0
#define W_DATE 1
#define W_RW_TYPE 2
#define W_RW_AMNT 3
#define W_REAL_DATE 4

#define BASIC_PROPS ({ P_TYPE,P_DOMAIN,P_START,P_END,P_STATUS,\
  P_CREATOR,P_RW_TYPE,P_RW_AMNT,P_DESC,P_ANNOUNCE,P_ANNOUNCE_MINS})

#define HISTORY_PROPS ({ H_TYPE,H_DOMAIN,H_START,H_WINNER })

#define FILTER_PROPS ({ P_TYPE,P_DOMAIN,P_DATE,P_STATUS,P_CREATOR })

#define PROP_TYPES ({ PT_INT,PT_STRING,PT_MEMO,PT_ARRAY,PT_DATETIME,\
  PT_BOOLEAN })

#define CE_SERVER 0
#define CE_FUNCTION 1
#define CE_SCHEDULE 2
#define CE_OWNER 3

#define FR_DAY 1
#define FR_WEEK 2

#define TM_RANDOM 1
#define TM_FIXED 2

#define DY_RANDOM 1
#define DY_FIXED 2

#define EVENT_I_NAME "_event_i_name"
#define EVENT_I_FREQ "_event_i_freq"
#define EVENT_I_TIME_TYPE "_event_i_time_type"
#define EVENT_I_DAY_TYPE "_event_i_day_type"
#define EVENT_I_TIME "_event_i_time"
#define EVENT_I_TO_ENTER "_event_i_to_enter"
#define EVENT_I_DAYS "_event_i_days"

