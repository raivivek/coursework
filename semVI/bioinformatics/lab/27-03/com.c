/* Public Domain */
/* Written by Vivek Rai. */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_WIDTH 100

/* Categorize different amino acids */
const char HP[][4] = {"ALA", "GLY", "VAL", "ILE", "LEU", "PRO", "PHE", "TRP"};
const char NP[][4] = {"SER", "THR", "HIS", "CYS", "MET", "ASN", "GLU", "TYR"};
const char CC[][4] = {"ARG", "LYS", "ASP", "GLN"};

/* Create Atom object.*/
typedef struct {
    int number;
    char *residue;
    char *chain;
    char *element;
    float mass;
    float x;
    float y;
    float z;
} Atom;

/* Fetch substring between start and end codrdinates from the input string.*/
static char *substr(char *line, int start, int end) {
    size_t length = strlen(line);
    char *temp = (char *) malloc(length);
    int t=0;

    if (start > length || end < start || end < 0) {
        return 0;
    }

    start = start < 0 ? 0 : start;
    end = end > length ? length : end;

    for (size_t i=start-1; i < end && i != '\0'; ++i) {
        temp[t++] = line[i];
    }

    temp[t] = '\0';
    return temp;
}

/* Looks for presence of a string in the given array of strings of amino acids
 * (indicated by their three letter code). */
static bool in(const char c[][4], size_t length, char *to_match) {
    for (size_t i = 0; i < length; ++i) {
        if (strcmp(c[i], to_match) == 0) return true;
    }
    return false;
}

/* Checks whether a given ATOM line in PDB file corresponds to RNA. */
static bool is_rna(char *line) {
    char *aa = substr(line, 18, 20);
    if (aa[0] == ' ') return true;
    return false;
}

/* Instantiates an Atom object */
Atom create_atom(char *line) {
    Atom temp;

    temp.number  = atoi(substr(line, 7, 11));
    temp.residue = substr(line, 18, 20);
    temp.chain   = substr(line, 22, 22);
    temp.element = substr(line, 77, 78);
    temp.x       = atof(substr(line, 31, 38));
    temp.y       = atof(substr(line, 39, 46));
    temp.z       = atof(substr(line, 47, 54));

    if (strcmp(temp.element, " N")) temp.mass = 14.0;
    else if (strcmp(temp.element, " C")) temp.mass = 12.0;
    else if (strcmp(temp.element, " O")) temp.mass = 16.0;
    else temp.mass = 1.0;

    return temp;
}

void calculate_com(Atom atoms[], int atom_count) {
    float h_x = 0, h_y = 0, h_z = 0;
    float hn = 0;

    float np_x = 0, np_y = 1.0, np_z = 0;
    float npn = 0;

    float c_x = 0, c_y = 0, c_z = 0;
    float cn = 0;

    for (int i = 0; i < atom_count; ++i) {
        if (in(HP, 8, atoms[i].residue)) {
            h_x += atoms[i].mass * atoms[i].x;
            h_y += atoms[i].mass * atoms[i].y;
            h_z += atoms[i].mass * atoms[i].z;
            hn += atoms[i].mass;
        } else if (in(NP, 8, atoms[i].residue)) {
            np_x += atoms[i].mass * atoms[i].x;
            np_y += atoms[i].mass * atoms[i].y;
            np_z += atoms[i].mass * atoms[i].z;
            npn += atoms[i].mass;
        } else if (in(CC, 4, atoms[i].residue)) {
            c_x += atoms[i].mass * atoms[i].x;
            c_y += atoms[i].mass * atoms[i].y;
            c_z += atoms[i].mass * atoms[i].z;
            cn += atoms[i].mass;
        }
    }

    fprintf(stdout, "Hydrophobic CoM:        %f %f %f\n", h_x/hn, h_y/hn, h_z/hn);
    fprintf(stdout, "Neutral/Polar CoM:      %f %f %f\n", np_x/npn, np_y/npn, np_z/npn);
    fprintf(stdout, "Charged (Pos, Neg) CoM: %f %f %f\n", c_x/cn, c_y/cn, c_z/cn);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stdout, "Please provide PDB filename as first parameter.");
        exit(-1);
    }

    char *pdb_file =  argv[1];

    FILE *fp;
    fp = fopen(pdb_file, "r");

    if (fp == NULL) fprintf(stderr, "Error opening file!");
    else {
        char line[MAX_WIDTH];
        Atom atoms[10000];
        int atom_count = -1;

        /* Read each line of the PDB file one by one and create an array
         * of ATOM objects.*/
        while (fgets(line, MAX_WIDTH, fp) != NULL) {
            if (!strncmp (line, "ATOM", 4)) {
                if (!is_rna(line)) {
                    atoms[++atom_count] = create_atom(line);
                }
            }
        }
        calculate_com(atoms, atom_count);
    }

    return 0;
}
