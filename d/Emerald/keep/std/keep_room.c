inherit "/std/room";

int *dimensions = ({ 0, 0 });
int cost = 0;
int completion_time = 0;
string keep_master;

void
create_keep_room()
{
}

static nomask void
create_room()
{
    create_keep_room();
}

void
set_structure_name(string name)
{
    set_name(name);
}

string
query_structure_name()
{
    return query_name();
}

void set_structure_cost(int cc)
{
    cost = cc;
}

int
query_structure_ocst()
{
    return cost;
}

void
set_structure_completion_time(int t)
{
    completion_time = t;
}

int
query_structure_completion_time()
{
    return completion_time;
}

void
set_dimensions(int x, int y)
{
    dimensions = ({ x, y });
}
  
int *
query_dimensions()
{
    return dimensions;
}

void
set_keep_master_file(string filename)
{
    keep_master = filename;
}

string
query_keep_master_file()
{
    return keep_master;
}
