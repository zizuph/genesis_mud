#define DIR "/d/Rhovanion/hazelnut/mirkwood"

exec string c, d=DIR;
string p=get_dir(d+"/*");
int i;
for (i=0; i<sizeof(path); i++)
if (sscanf(path[i], "%s.c",c) == 1)(d+c)->load_me_up();
