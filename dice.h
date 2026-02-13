typedef struct {
    //uint32_t die_color; // Not used in initial REPL version, but once we move to art assets this can be used to color the die
    char* name;
    unsigned char sides[6];
} Fellowship_die;

typedef struct {
    char *names[6];
}Combat_die;

typedef struct {
    unsigned char sides[6];
}Encounter_die;
