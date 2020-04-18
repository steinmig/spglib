use crate::cell::Cell;
use crate::dataset::Dataset;

pub fn bcc_cell() -> Cell {
    let lattice = [[4., 0., 0.], [0., 4., 0.], [0., 0., 4.]];
    let positions = &[[0., 0., 0.], [0.5, 0.5, 0.5]];
    let types = &[1, 1];
    Cell::new(lattice, positions, types)
}

pub fn distorted_bcc_cell() -> Cell {
    let lattice = [[3.97, 0., 0.], [0., 4.03, 0.], [0., 0., 4.]];
    let positions = &[[0.002, 0., 0.], [0.5, 0.5001, 0.5]];
    let types = &[1, 1];
    Cell::new(lattice, positions, types)
}

pub fn corrundum_cell() -> Cell {
    let lattice = [
        [4.8076344022756095, -2.4038172011378047, 0.],
        [0., 4.1635335244786962, 0.],
        [0., 0., 13.1172699198127543],
    ];
    let positions = &[
        [0.0000000000000000, 0.0000000000000000, 0.3521850942289043],
        [0.6666666666666643, 0.3333333333333357, 0.6855184275622400],
        [0.3333333333333357, 0.6666666666666643, 0.0188517608955686],
        [0.0000000000000000, 0.0000000000000000, 0.6478149057711028],
        [0.6666666666666643, 0.3333333333333357, 0.9811482391044314],
        [0.3333333333333357, 0.6666666666666643, 0.3144815724377600],
        [0.0000000000000000, 0.0000000000000000, 0.1478149057710957],
        [0.6666666666666643, 0.3333333333333357, 0.4811482391044314],
        [0.3333333333333357, 0.6666666666666643, 0.8144815724377600],
        [0.0000000000000000, 0.0000000000000000, 0.8521850942288972],
        [0.6666666666666643, 0.3333333333333357, 0.1855184275622400],
        [0.3333333333333357, 0.6666666666666643, 0.5188517608955686],
        [0.3061673906454899, 0.0000000000000000, 0.2500000000000000],
        [0.9728340573121541, 0.3333333333333357, 0.5833333333333357],
        [0.6395007239788255, 0.6666666666666643, 0.9166666666666643],
        [0.6938326093545102, 0.0000000000000000, 0.7500000000000000],
        [0.3604992760211744, 0.3333333333333357, 0.0833333333333357],
        [0.0271659426878458, 0.6666666666666643, 0.4166666666666643],
        [0.0000000000000000, 0.3061673906454899, 0.2500000000000000],
        [0.6666666666666643, 0.6395007239788255, 0.5833333333333357],
        [0.3333333333333357, 0.9728340573121541, 0.9166666666666643],
        [0.0000000000000000, 0.6938326093545102, 0.7500000000000000],
        [0.6666666666666643, 0.0271659426878458, 0.0833333333333357],
        [0.3333333333333357, 0.3604992760211744, 0.4166666666666643],
        [0.6938326093545102, 0.6938326093545102, 0.2500000000000000],
        [0.3604992760211744, 0.0271659426878458, 0.5833333333333357],
        [0.0271659426878458, 0.3604992760211744, 0.9166666666666643],
        [0.3061673906454899, 0.3061673906454899, 0.7500000000000000],
        [0.9728340573121541, 0.6395007239788255, 0.0833333333333357],
        [0.6395007239788255, 0.9728340573121541, 0.4166666666666643],
    ];
    let mut types = [1; 30];
    for i in 12..30 {
        types[i] = 2;
    }
    Cell::new(lattice, positions, &types)
}

pub fn distorted_corrundum_cell() -> Cell {
    let lattice = [
        [4.8076344022756095, -2.4038172011378047, 0.],
        [0., 4.1635335244786962, 0.],
        [0., 0., 13.1172699198127543],
    ];
    let positions = &[
        [0.0000000000000000, 0.0000000000000000, 0.3521850942289043],
        [0.6666666666666643, 0.3333333333333357, 0.6855184275622400],
        [0.3333333333333357, 0.6666666666666643, 0.0188517608955686],
        [0.0000000000000000, 0.0000000000000000, 0.6478149057711028],
        [0.6666666666666643, 0.3333333333333357, 0.9811482391044314],
        [0.3333333333333357, 0.6666666666666643, 0.3144815724377600],
        [0.0000000000000000, 0.0000000000000000, 0.1478149057710957],
        [0.6666666666666643, 0.3333333333333357, 0.4811482391044314],
        [0.3333333333333357, 0.6666666666666643, 0.8144815724377600],
        [0.0000000000000000, 0.0000000000000000, 0.8521850942288972],
        [0.6666666666666643, 0.3333333333333357, 0.1855184275622400],
        [0.3333333333333357, 0.6666666666666643, 0.5188517608955686],
        [0.3061673906454899, 0.0000000000000000, 0.2500000000000000],
        [0.9728340573121541, 0.3333333333333357, 0.5833333333333357],
        [0.6395007239788255, 0.6666666666666643, 0.9166666666666643],
        [0.6938326093545102, 0.0000000000000000, 0.7500000000000000],
        [0.3604992760211744, 0.3333333333333357, 0.0833333333333357],
        [0.0271659426878458, 0.6666666666666643, 0.4166666666666643],
        [0.0000000000000000, 0.3061673906454899, 0.2500000000000000],
        [0.6666666666666643, 0.6395007239788255, 0.5833333333333357],
        [0.3333333333333357, 0.9728340573121541, 0.9166666666666643],
        [0.0000000000000000, 0.6938326093545102, 0.7500000000000000],
        [0.6666666666666643, 0.0271659426878458, 0.0833333333333357],
        [0.3333333333333357, 0.3604992760211744, 0.4166666666666643],
        [0.6938326093545102, 0.6938326093545102, 0.2500000000000000],
        [0.3604992760211744, 0.0271659426878458, 0.5833333333333357],
        [0.0271659426878458, 0.3604992760211744, 0.9166666666666643],
        [0.3061673906454899, 0.3061673906454899, 0.7500000000000000],
        [0.9728340573121541, 0.6395007239788255, 0.0833333333333357],
        [0.6395007239788255, 0.9728340573121541, 0.4166666666666643],
    ];

    let mut types = [1; 30];
    for i in 12..30 {
        types[i] = 2;
    }
    Cell::new(lattice, positions, &types)
}

// Returns a lattice consisting of 2 rutile unit cells
pub fn rutile_cell() -> Cell {
    let lattice = [[4., 0., 0.], [0., 4., 0.], [0., 0., 4.]];
    let positions = &[
        [0., 0., 0.],
        [0.5, 0.5, 0.25],
        [0.3, 0.3, 0.],
        [0.7, 0.7, 0.],
        [0.2, 0.8, 0.25],
        [0.8, 0.2, 0.25],
        [0., 0., 0.5],
        [0.5, 0.5, 0.75],
        [0.3, 0.3, 0.5],
        [0.7, 0.7, 0.5],
        [0.2, 0.8, 0.75],
        [0.8, 0.2, 0.75],
    ];
    let types = &[1, 1, 2, 2, 2, 2, 1, 1, 2, 2, 2, 2];
    Cell::new(lattice, positions, types)
}

pub fn validate_rutile_cell_dataset(dataset: &Dataset) {
    assert_eq!(dataset.spacegroup_number, 136);
    assert_eq!(dataset.hall_number, 419);
    assert_eq!(dataset.international_symbol.as_str(), "P4_2/mnm");
    assert_eq!(dataset.hall_symbol.as_str(), "-P 4n 2n");
    assert_eq!(dataset.choice.as_str(), "");
    assert_eq!(
        dataset.transformation_matrix,
        [[1., 0., 0.], [0., 1., 0.], [0., 0., 2.]]
    );
    assert_eq!(dataset.origin_shift, [0., 0., 0.]);
    assert_eq!(dataset.n_operations, 32);
    assert_eq!(
        dataset.rotations[..],
        [
            [[1, 0, 0], [0, 1, 0], [0, 0, 1]],
            [[-1, 0, 0], [0, -1, 0], [0, 0, -1]],
            [[0, -1, 0], [1, 0, 0], [0, 0, 1]],
            [[0, 1, 0], [-1, 0, 0], [0, 0, -1]],
            [[-1, 0, 0], [0, -1, 0], [0, 0, 1]],
            [[1, 0, 0], [0, 1, 0], [0, 0, -1]],
            [[0, 1, 0], [-1, 0, 0], [0, 0, 1]],
            [[0, -1, 0], [1, 0, 0], [0, 0, -1]],
            [[1, 0, 0], [0, -1, 0], [0, 0, -1]],
            [[-1, 0, 0], [0, 1, 0], [0, 0, 1]],
            [[0, -1, 0], [-1, 0, 0], [0, 0, -1]],
            [[0, 1, 0], [1, 0, 0], [0, 0, 1]],
            [[-1, 0, 0], [0, 1, 0], [0, 0, -1]],
            [[1, 0, 0], [0, -1, 0], [0, 0, 1]],
            [[0, 1, 0], [1, 0, 0], [0, 0, -1]],
            [[0, -1, 0], [-1, 0, 0], [0, 0, 1]],
            [[1, 0, 0], [0, 1, 0], [0, 0, 1]],
            [[-1, 0, 0], [0, -1, 0], [0, 0, -1]],
            [[0, -1, 0], [1, 0, 0], [0, 0, 1]],
            [[0, 1, 0], [-1, 0, 0], [0, 0, -1]],
            [[-1, 0, 0], [0, -1, 0], [0, 0, 1]],
            [[1, 0, 0], [0, 1, 0], [0, 0, -1]],
            [[0, 1, 0], [-1, 0, 0], [0, 0, 1]],
            [[0, -1, 0], [1, 0, 0], [0, 0, -1]],
            [[1, 0, 0], [0, -1, 0], [0, 0, -1]],
            [[-1, 0, 0], [0, 1, 0], [0, 0, 1]],
            [[0, -1, 0], [-1, 0, 0], [0, 0, -1]],
            [[0, 1, 0], [1, 0, 0], [0, 0, 1]],
            [[-1, 0, 0], [0, 1, 0], [0, 0, -1]],
            [[1, 0, 0], [0, -1, 0], [0, 0, 1]],
            [[0, 1, 0], [1, 0, 0], [0, 0, -1]],
            [[0, -1, 0], [-1, 0, 0], [0, 0, 1]]
        ]
    );
    assert_eq!(
        dataset.translations[..],
        [
            [0.0, 0.0, 0.0],
            [0.0, 0.0, 0.0],
            [0.5, 0.5, 0.25],
            [0.5, 0.5, 0.25],
            [0.0, 0.0, 0.0],
            [0.0, 0.0, 0.0],
            [0.5, 0.5, 0.25],
            [0.5, 0.5, 0.25],
            [0.5, 0.5, 0.25],
            [0.5, 0.5, 0.25],
            [0.0, 0.0, 0.0],
            [0.0, 0.0, 0.0],
            [0.5, 0.5, 0.25],
            [0.5, 0.5, 0.25],
            [0.0, 0.0, 0.0],
            [0.0, 0.0, 0.0],
            [0.0, 0.0, 0.5],
            [0.0, 0.0, 0.5],
            [0.5, 0.5, 0.75],
            [0.5, 0.5, 0.75],
            [0.0, 0.0, 0.5],
            [0.0, 0.0, 0.5],
            [0.5, 0.5, 0.75],
            [0.5, 0.5, 0.75],
            [0.5, 0.5, 0.75],
            [0.5, 0.5, 0.75],
            [0.0, 0.0, 0.5],
            [0.0, 0.0, 0.5],
            [0.5, 0.5, 0.75],
            [0.5, 0.5, 0.75],
            [0.0, 0.0, 0.5],
            [0.0, 0.0, 0.5]
        ]
    );
    assert_eq!(dataset.n_atoms, 12);
    assert_eq!(dataset.wyckoffs[..], [0, 0, 5, 5, 5, 5, 0, 0, 5, 5, 5, 5]);
    // TODO: test site_symmetry_symbols when implemented
    assert_eq!(
        dataset.equivalent_atoms[..],
        [0, 0, 2, 2, 2, 2, 0, 0, 2, 2, 2, 2]
    );
    assert_eq!(
        dataset.mapping_to_primitive[..],
        [0, 1, 2, 3, 4, 5, 0, 1, 2, 3, 4, 5]
    );
    assert_eq!(dataset.n_std_atoms, 6);
    assert_eq!(
        dataset.std_lattice,
        [[4.0, 0.0, 0.0], [0.0, 4.0, 0.0], [0.0, 0.0, 2.0]]
    );
    assert_eq!(dataset.std_types[..], [1, 1, 2, 2, 2, 2]);
    assert_eq!(
        dataset.std_positions[..],
        [
            [0.0, 0.0, 0.0],
            [0.5, 0.5, 0.5],
            [0.3, 0.3, 0.0],
            [0.7, 0.7, 0.0],
            [0.2, 0.8, 0.5],
            [0.8, 0.2, 0.5]
        ]
    );
    assert_eq!(
        dataset.std_rotation_matrix,
        [[1.0, 0.0, 0.0], [0.0, 1.0, 0.0], [0.0, 0.0, 1.0]]
    );
    assert_eq!(dataset.std_mapping_to_primitive[..], [0, 1, 2, 3, 4, 5]);
    assert_eq!(dataset.pointgroup_symbol.as_str(), "4/mmm");
}