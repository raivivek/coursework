#!/usr/bin/python3
# vim:fileencoding=utf-8

""" Calculates the number and percentage composition of different
types of amino acid residues within a protein."""

__author__ = "Vivek Rai"

HYDROPHOBIC_AA = ['ALA', 'GLY', 'VAL', 'ILE', 'LEU', 'PRO']
POSITIVE_AA    = ['ARG', 'LYS']
NEGATIVE_AA    = ['ASP', 'GLU']
NEUTRAL_AA     = ['SER', 'THR', 'HIS', 'CYS', 'MET', 'ASN', 'GLN']
AROMATIC_AA    = ['PHE', 'TYR', 'TRP']

def get_composition(pdb_file):
    count = {
            'TOTAL_AA'       : 0,
            'HYDROPHOBIC_AA' : 0,
            'POSITIVE_AA'    : 0,
            'NEGATIVE_AA'    : 0,
            'NEUTRAL_AA'     : 0,
            'AROMATIC_AA'    : 0
            }

    for line in pdb_file.readlines():
        if line.startswith('SEQRES'):
            residues = line.split()[4:]
            count['TOTAL_AA'] += len(residues)

            for residue in residues:
                if residue in HYDROPHOBIC_AA:
                    count['HYDROPHOBIC_AA']  += 1
                elif residue in POSITIVE_AA:
                    count['POSITIVE_AA']     += 1
                elif residue in NEGATIVE_AA:
                    count['NEGATIVE_AA']     += 1
                elif residue in NEUTRAL_AA:
                    count['NEUTRAL_AA']      += 1
                elif residue in AROMATIC_AA:
                    count['AROMATIC_AA']     += 1

    return count

if __name__ == "__main__":
    with open('12AS.pdb', 'r', encoding='utf-8') as f:
        composition = get_composition(f)
        total_aa    = composition.pop('TOTAL_AA')

        # pretty print the obtaiend results
        print('{:15}: 660, 100%'.format('TOTAL_AA'))
        for key, value in composition.items():
            print("{:15}: {:3}/{}, {:.2f} %".format(key,
                                                    value,
                                                    total_aa,
                                                    100*value/total_aa))
