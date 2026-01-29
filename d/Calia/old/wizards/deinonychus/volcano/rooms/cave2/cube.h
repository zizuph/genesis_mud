#define	MAX_EXITS 10	/* max. number of exits a room can have */

#define	N  0		/* directions */
#define	NE 1
#define	E  2
#define	SE 3
#define	U  4
#define	S  5
#define	SW 6
#define	W  7
#define	NW 8
#define	D  9

#define L  3		/* Length of cube */

#define BITFIELD 1	/* quest-bit-bitfield */
#define BITNUM   3	/* quest-bit */

#define REWARD 10000		/* reward for the solving */
#define SMALL_REWARD 1000	/* reward for solving it again */

#define MAX_EDGES 50
#define MIN_EDGES 30

#define AV -1
#define NAV 0
#define STABLE 1
#define INSTABLE 2
#define COUNT vertex[x][y][z][MAX_EXITS]

#define SEED 100
#define NULL 0

#define PASSWORD ROOM("maze00")->query_password()

#define LOGFILE DINO + "log/cubequest.log"

/* prototypes */
void init_vertex();
void init_reachable();
void set_enter_point(int reachcount);
void make_path();
mixed make_exits();
mixed remove_exits();
int moving(string direction);
int do_pull(string what);
void give_reward();
void wizinfo();
void draw_part(int n);
void draw_0();
void draw_1();
void draw_2();

string *dirstring =	/* used to convert directions coded in integers to strings */
  ({"north", "northeast", "east", "southeast", "up",
    "south", "southwest", "west", "northwest", "down"});
mapping dirint =	/* used to convert directions coded in strings to integers */
  (["north": N, "northeast": NE, "east": E, "southeast": SE, "up": U,
    "south": S, "southwest": SW, "west": W, "northwest": NW, "down": D]);
int *conter_dir =	/* used to find out the conterdirection */
  ({S, SW, W, NW, D, N, NE, E, SE, U});

