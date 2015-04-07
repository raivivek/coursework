# -*- coding: utf-8 -*-
#!usr/bin/python3

# p_centerofmass.py

""" Compute the center of mass of the protein structure based on
the information obtained from reading the PDB file of the target protein.
"""

__AUTHOR__ = 'Vivek Rai'
__DATE__ = '20 May 2014'

from sys import stdin
import urllib.request
from os import path
from Bio.PDB.PDBParser import PDBParser
import numpy as np

PDEB_EBI_URL = 'http://www.ebi.ac.uk/pdbe-srv/view/files/'

def center_of_mass(pdbfile):
    """ Calculates the center of the mass of given input protein data file.

    Returns
    -------
    list
        [x, y, z] coordinates of CoM.
    """

    with open(pdbfile, 'r') as f:
        parser = PDBParser(PERMISSIVE=True)
        structure = parser.get_structure(pdbfile, f.read())

        total_atoms_mass = []
        for atoms in structure.get_atoms():
            total_atoms_mass.append([atoms.coord, atoms.mass])

        num_atoms = len(total_atoms_mass)

        # Total mass of the atoms
        total_mass = sum([total_atoms_mass[i][1] for i in range(num_atoms)])

        center_of_mass = [sum([
                               total_atoms_mass[i][0][j] * total_atoms_mass[i][1]
                               for i in range(num_atoms)
                               ])
                          for j in range(3)]

        return np.array(center_of_mass) / total_mass


def main():
    print("Enter the PDB ID (for eg, 4hhb.pdb)\t")
    pdbfile = stdin.readline().strip()
    if len(pdbfile) == 0:
        pdbfile = '3hhb.pdb'

    if not path.exists(pdbfile):
        # PDB files are downloaded from PDBe.org database if not found.
        # See references.
        print('Downloading ...')
        try:
            url = '{}{}'.format(PDBE_EBI_URL, pdbfile)
            urllib.request.urlretrieve(url, pdbfile)
            result = center_of_mass(pdbfile)
        except:
            print("Cannot open url for {}\n".format(pdbfile))

    return result

if __name__ == '__main__':
    print(main())
