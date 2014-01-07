/* tetrahedron_method.c */
/* Copyright (C) 2014 Atsushi Togo */

#include "mathfunc.h"
#include "debug.h"


/*      6-------7             */
/*     /|      /|             */
/*    / |     / |             */
/*   4-------5  |             */
/*   |  2----|--3             */
/*   | /     | /              */
/*   |/      |/	              */
/*   0-------1	              */
/*  		              */
/*  i: vec        neighbours  */
/*  0: O          1, 2, 4     */
/*  1: a          0, 3, 5     */
/*  2: b          0, 3, 6     */
/*  3: a + b      1, 2, 7     */
/*  4: c          0, 5, 6     */
/*  5: c + a      1, 4, 7     */
/*  6: c + b      2, 4, 7     */
/*  7: c + a + b  3, 5, 6     */


static int main_diagonals[4][3] = {{ 1, 1, 1},  /* 0-7 */
				   {-1, 1, 1},  /* 1-6 */
				   { 1,-1, 1},  /* 2-5 */
				   { 1, 1,-1}}; /* 3-4 */

static int db_relative_grid_address[4][24][4][3] = {
  {
    { { 0,  0,  0}, { 1,  0,  0}, { 1,  1,  0}, { 1,  1,  1}, },
    { { 0,  0,  0}, { 1,  0,  0}, { 1,  0,  1}, { 1,  1,  1}, },
    { { 0,  0,  0}, { 0,  1,  0}, { 1,  1,  0}, { 1,  1,  1}, },
    { { 0,  0,  0}, { 0,  1,  0}, { 0,  1,  1}, { 1,  1,  1}, },
    { { 0,  0,  0}, { 0,  0,  1}, { 1,  0,  1}, { 1,  1,  1}, },
    { { 0,  0,  0}, { 0,  0,  1}, { 0,  1,  1}, { 1,  1,  1}, },
    { { 0,  0,  0}, { 0,  1,  0}, { 0,  1,  1}, {-1,  0,  0}, },
    { { 0,  0,  0}, { 0,  0,  1}, { 0,  1,  1}, {-1,  0,  0}, },
    { { 0,  0,  0}, { 1,  0,  0}, { 1,  0,  1}, { 0, -1,  0}, },
    { { 0,  0,  0}, { 0,  0,  1}, { 1,  0,  1}, { 0, -1,  0}, },
    { { 0,  0,  0}, { 0,  0,  1}, {-1, -1,  0}, { 0, -1,  0}, },
    { { 0,  0,  0}, { 0,  0,  1}, {-1, -1,  0}, {-1,  0,  0}, },
    { { 0,  0,  0}, { 1,  0,  0}, { 1,  1,  0}, { 0,  0, -1}, },
    { { 0,  0,  0}, { 0,  1,  0}, { 1,  1,  0}, { 0,  0, -1}, },
    { { 0,  0,  0}, { 0,  1,  0}, {-1,  0, -1}, { 0,  0, -1}, },
    { { 0,  0,  0}, { 0,  1,  0}, {-1,  0, -1}, {-1,  0,  0}, },
    { { 0,  0,  0}, { 1,  0,  0}, { 0, -1, -1}, { 0,  0, -1}, },
    { { 0,  0,  0}, { 1,  0,  0}, { 0, -1, -1}, { 0, -1,  0}, },
    { { 0,  0,  0}, {-1, -1, -1}, { 0, -1, -1}, { 0,  0, -1}, },
    { { 0,  0,  0}, {-1, -1, -1}, { 0, -1, -1}, { 0, -1,  0}, },
    { { 0,  0,  0}, {-1, -1, -1}, {-1,  0, -1}, { 0,  0, -1}, },
    { { 0,  0,  0}, {-1, -1, -1}, {-1,  0, -1}, {-1,  0,  0}, },
    { { 0,  0,  0}, {-1, -1, -1}, {-1, -1,  0}, { 0, -1,  0}, },
    { { 0,  0,  0}, {-1, -1, -1}, {-1, -1,  0}, {-1,  0,  0}, },
  },
  {
    { { 0,  0,  0}, { 1,  0,  0}, { 0,  1,  0}, { 0,  1,  1}, },
    { { 0,  0,  0}, { 1,  0,  0}, { 0,  0,  1}, { 0,  1,  1}, },
    { { 0,  0,  0}, {-1,  1,  0}, {-1,  1,  1}, {-1,  0,  0}, },
    { { 0,  0,  0}, {-1,  0,  1}, {-1,  1,  1}, {-1,  0,  0}, },
    { { 0,  0,  0}, {-1,  1,  0}, { 0,  1,  0}, {-1,  1,  1}, },
    { { 0,  0,  0}, { 0,  1,  0}, {-1,  1,  1}, { 0,  1,  1}, },
    { { 0,  0,  0}, {-1,  0,  1}, { 0,  0,  1}, {-1,  1,  1}, },
    { { 0,  0,  0}, { 0,  0,  1}, {-1,  1,  1}, { 0,  1,  1}, },
    { { 0,  0,  0}, { 0,  0,  1}, { 0, -1,  0}, { 1, -1,  0}, },
    { { 0,  0,  0}, { 1,  0,  0}, { 0,  0,  1}, { 1, -1,  0}, },
    { { 0,  0,  0}, {-1,  0,  1}, { 0, -1,  0}, {-1,  0,  0}, },
    { { 0,  0,  0}, {-1,  0,  1}, { 0,  0,  1}, { 0, -1,  0}, },
    { { 0,  0,  0}, { 0,  1,  0}, { 0,  0, -1}, { 1,  0, -1}, },
    { { 0,  0,  0}, { 1,  0,  0}, { 0,  1,  0}, { 1,  0, -1}, },
    { { 0,  0,  0}, {-1,  1,  0}, { 0,  0, -1}, {-1,  0,  0}, },
    { { 0,  0,  0}, {-1,  1,  0}, { 0,  1,  0}, { 0,  0, -1}, },
    { { 0,  0,  0}, { 0, -1, -1}, { 1, -1, -1}, { 0,  0, -1}, },
    { { 0,  0,  0}, { 0, -1, -1}, { 1, -1, -1}, { 0, -1,  0}, },
    { { 0,  0,  0}, { 1, -1, -1}, { 0,  0, -1}, { 1,  0, -1}, },
    { { 0,  0,  0}, { 1,  0,  0}, { 1, -1, -1}, { 1,  0, -1}, },
    { { 0,  0,  0}, { 1, -1, -1}, { 0, -1,  0}, { 1, -1,  0}, },
    { { 0,  0,  0}, { 1,  0,  0}, { 1, -1, -1}, { 1, -1,  0}, },
    { { 0,  0,  0}, { 0, -1, -1}, { 0,  0, -1}, {-1,  0,  0}, },
    { { 0,  0,  0}, { 0, -1, -1}, { 0, -1,  0}, {-1,  0,  0}, },
  },
  {
    { { 0,  0,  0}, { 1,  0,  0}, { 0,  1,  0}, { 1,  0,  1}, },
    { { 0,  0,  0}, { 0,  1,  0}, { 0,  0,  1}, { 1,  0,  1}, },
    { { 0,  0,  0}, {-1,  1,  0}, { 0,  0,  1}, {-1,  0,  0}, },
    { { 0,  0,  0}, {-1,  1,  0}, { 0,  1,  0}, { 0,  0,  1}, },
    { { 0,  0,  0}, { 1, -1,  1}, { 0, -1,  0}, { 1, -1,  0}, },
    { { 0,  0,  0}, { 0, -1,  1}, { 1, -1,  1}, { 0, -1,  0}, },
    { { 0,  0,  0}, { 1,  0,  0}, { 1, -1,  1}, { 1, -1,  0}, },
    { { 0,  0,  0}, { 1,  0,  0}, { 1, -1,  1}, { 1,  0,  1}, },
    { { 0,  0,  0}, { 0, -1,  1}, { 1, -1,  1}, { 0,  0,  1}, },
    { { 0,  0,  0}, { 1, -1,  1}, { 0,  0,  1}, { 1,  0,  1}, },
    { { 0,  0,  0}, { 0, -1,  1}, { 0, -1,  0}, {-1,  0,  0}, },
    { { 0,  0,  0}, { 0, -1,  1}, { 0,  0,  1}, {-1,  0,  0}, },
    { { 0,  0,  0}, { 1,  0,  0}, { 0,  0, -1}, { 0,  1, -1}, },
    { { 0,  0,  0}, { 1,  0,  0}, { 0,  1,  0}, { 0,  1, -1}, },
    { { 0,  0,  0}, {-1,  0, -1}, { 0,  0, -1}, {-1,  1, -1}, },
    { { 0,  0,  0}, {-1,  0, -1}, {-1,  1, -1}, {-1,  0,  0}, },
    { { 0,  0,  0}, { 0,  0, -1}, {-1,  1, -1}, { 0,  1, -1}, },
    { { 0,  0,  0}, { 0,  1,  0}, {-1,  1, -1}, { 0,  1, -1}, },
    { { 0,  0,  0}, {-1,  1,  0}, {-1,  1, -1}, {-1,  0,  0}, },
    { { 0,  0,  0}, {-1,  1,  0}, { 0,  1,  0}, {-1,  1, -1}, },
    { { 0,  0,  0}, { 0,  0, -1}, { 0, -1,  0}, { 1, -1,  0}, },
    { { 0,  0,  0}, { 1,  0,  0}, { 0,  0, -1}, { 1, -1,  0}, },
    { { 0,  0,  0}, {-1,  0, -1}, { 0,  0, -1}, { 0, -1,  0}, },
    { { 0,  0,  0}, {-1,  0, -1}, { 0, -1,  0}, {-1,  0,  0}, },
  },
  {
    { { 0,  0,  0}, { 1,  0,  0}, { 1,  1,  0}, { 0,  0,  1}, },
    { { 0,  0,  0}, { 0,  1,  0}, { 1,  1,  0}, { 0,  0,  1}, },
    { { 0,  0,  0}, { 0,  1,  0}, {-1,  0,  1}, {-1,  0,  0}, },
    { { 0,  0,  0}, { 0,  1,  0}, {-1,  0,  1}, { 0,  0,  1}, },
    { { 0,  0,  0}, { 1,  0,  0}, { 0, -1,  1}, { 0, -1,  0}, },
    { { 0,  0,  0}, { 1,  0,  0}, { 0, -1,  1}, { 0,  0,  1}, },
    { { 0,  0,  0}, {-1, -1,  1}, {-1, -1,  0}, { 0, -1,  0}, },
    { { 0,  0,  0}, {-1, -1,  1}, {-1, -1,  0}, {-1,  0,  0}, },
    { { 0,  0,  0}, {-1, -1,  1}, { 0, -1,  1}, { 0, -1,  0}, },
    { { 0,  0,  0}, {-1, -1,  1}, {-1,  0,  1}, {-1,  0,  0}, },
    { { 0,  0,  0}, {-1, -1,  1}, { 0, -1,  1}, { 0,  0,  1}, },
    { { 0,  0,  0}, {-1, -1,  1}, {-1,  0,  1}, { 0,  0,  1}, },
    { { 0,  0,  0}, { 0,  0, -1}, { 1,  0, -1}, { 1,  1, -1}, },
    { { 0,  0,  0}, { 0,  0, -1}, { 0,  1, -1}, { 1,  1, -1}, },
    { { 0,  0,  0}, { 1,  0,  0}, { 1,  0, -1}, { 1,  1, -1}, },
    { { 0,  0,  0}, { 0,  1,  0}, { 0,  1, -1}, { 1,  1, -1}, },
    { { 0,  0,  0}, { 1,  0,  0}, { 1,  1,  0}, { 1,  1, -1}, },
    { { 0,  0,  0}, { 0,  1,  0}, { 1,  1,  0}, { 1,  1, -1}, },
    { { 0,  0,  0}, { 0,  0, -1}, { 0,  1, -1}, {-1,  0,  0}, },
    { { 0,  0,  0}, { 0,  1,  0}, { 0,  1, -1}, {-1,  0,  0}, },
    { { 0,  0,  0}, { 0,  0, -1}, { 1,  0, -1}, { 0, -1,  0}, },
    { { 0,  0,  0}, { 1,  0,  0}, { 1,  0, -1}, { 0, -1,  0}, },
    { { 0,  0,  0}, { 0,  0, -1}, {-1, -1,  0}, { 0, -1,  0}, },
    { { 0,  0,  0}, { 0,  0, -1}, {-1, -1,  0}, {-1,  0,  0}, },
  },
};


static int get_main_diagonal(SPGCONST double rec_lattice[3][3]);
static int sort_omegas(double v[4]);
static double _f(const int n,
		 const int m,
		 const double omega,
		 const double vertices_omegas[4]);
static double _J(const int i,
		 const int ci,
		 const double omega,
		 const double vertices_omegas[4]);
static double _I(const int i,
		 const int ci,
		 const double omega,
		 const double vertices_omegas[4]);
static double _n(const int i,
		 const double omega,
		 const double vertices_omegas[4]);
static double _g(const int i,
		 const double omega,
		 const double vertices_omegas[4]);
static double _n_0(void);
static double _n_1(const double omega,
		   const double vertices_omegas[4]);
static double _n_2(const double omega,
		   const double vertices_omegas[4]);
static double _n_3(const double omega,
		   const double vertices_omegas[4]);
static double _n_4(void);
static double _g_0(void);
static double _g_1(const double omega,
		   const double vertices_omegas[4]);
static double _g_2(const double omega,
		   const double vertices_omegas[4]);
static double _g_3(const double omega,
		   const double vertices_omegas[4]);
static double _g_4(void);
static double _J_0(void);
static double _J_10(const double omega,
		    const double vertices_omegas[4]);
static double _J_11(const double omega,
		    const double vertices_omegas[4]);
static double _J_12(const double omega,
		    const double vertices_omegas[4]);
static double _J_13(const double omega,
		    const double vertices_omegas[4]);
static double _J_20(const double omega,
		    const double vertices_omegas[4]);
static double _J_21(const double omega,
		    const double vertices_omegas[4]);
static double _J_22(const double omega,
		    const double vertices_omegas[4]);
static double _J_23(const double omega,
		    const double vertices_omegas[4]);
static double _J_30(const double omega,
		    const double vertices_omegas[4]);
static double _J_31(const double omega,
		    const double vertices_omegas[4]);
static double _J_32(const double omega,
		    const double vertices_omegas[4]);
static double _J_33(const double omega,
		    const double vertices_omegas[4]);
static double _J_4(void);
static double _I_0(void);
static double _I_10(const double omega,
		    const double vertices_omegas[4]);
static double _I_11(const double omega,
		    const double vertices_omegas[4]);
static double _I_12(const double omega,
		    const double vertices_omegas[4]);
static double _I_13(const double omega,
		    const double vertices_omegas[4]);
static double _I_20(const double omega,
		    const double vertices_omegas[4]);
static double _I_21(const double omega,
		    const double vertices_omegas[4]);
static double _I_22(const double omega,
		    const double vertices_omegas[4]);
static double _I_23(const double omega,
		    const double vertices_omegas[4]);
static double _I_30(const double omega,
		    const double vertices_omegas[4]);
static double _I_31(const double omega,
		    const double vertices_omegas[4]);
static double _I_32(const double omega,
		    const double vertices_omegas[4]);
static double _I_33(const double omega,
		    const double vertices_omegas[4]);
static double _I_4(void);


void thm_get_relative_grid_address(int relative_grid_address[24][4][3],
				   SPGCONST double rec_lattice[3][3])
{
  int i, j, k, main_diag_index;

  main_diag_index = get_main_diagonal(rec_lattice);
 
  for (i = 0; i < 24; i++) {
    for (j = 0; j < 4; j++) {
      for (k = 0; k < 3; k++) {
	relative_grid_address[i][j][k] =
	  db_relative_grid_address[main_diag_index][i][j][k];
      }
    }
  }
}

double thm_get_integration_weight(const double omega,
				  SPGCONST double tetrahedra_omegas[24][4])
{
  int i, j, k, ci;
  double v[4];
  double sum;

  sum = 0;

  for (i = 0; i < 24; i++) {
    for (j = 0; j < 4; j++) {
      v[j] = tetrahedra_omegas[i][j];
    }
    /* printf("%f %f %f %f: ", v[0], v[1], v[2], v[3], ci); */
    ci = sort_omegas(v);
    /* printf("%f %f %f %f, %d\n", v[0], v[1], v[2], v[3], ci); */
    if (omega < v[0]) {
      sum += _I(0, ci, omega, v) * _g(0, omega, v);
    } else {
      if (omega < v[1]) {
	sum += _I(1, ci, omega, v) * _g(1, omega, v);
      } else {
	if (omega < v[2]) {
	  sum += _I(2, ci, omega, v) * _g(2, omega, v);
	} else {
	  if (omega < v[3]) {
	    sum += _I(3, ci, omega, v) * _g(3, omega, v);
	  } else {
	    sum += _I(4, ci, omega, v) * _g(4, omega, v);
	  }
	}
      }
    }
  }
    
  return sum / 6;
}

static int sort_omegas(double v[4])
{
  int i;
  double w[4];

  i = 0;
  
  if (v[0] > v[1]) {
    w[0] = v[1];
    w[1] = v[0];
    i = 1;
  } else {
    w[0] = v[0];
    w[1] = v[1];
  }

  if (v[2] > v[3]) {
    w[2] = v[3];
    w[3] = v[2];
  } else {
    w[2] = v[2];
    w[3] = v[3];
  }

  if (w[0] > w[2]) {
    v[0] = w[2];
    v[1] = w[0];
    if (i == 0) {
      i = 4;
    }
  } else {
    v[0] = w[0];
    v[1] = w[2];
  }

  if (w[1] > w[3]) {
    v[3] = w[1];
    v[2] = w[3];
    if (i == 1) {
      i = 3;
    }
  } else {
    v[3] = w[3];
    v[2] = w[1];
    if (i == 1) {
      i = 5;
    }
  }

  if (v[1] > v[2]) {
    w[1] = v[1];
    v[1] = v[2];
    v[2] = w[1];
    if (i == 4) {
      i = 2;
    }
    if (i == 5) {
      i = 1;
    }
  } else {
    if (i == 4) {
      i = 1;
    }
    if (i == 5) {
      i = 2;
    }
  }
  return i;
}

static int get_main_diagonal(SPGCONST double rec_lattice[3][3])
{
  int i, shortest;
  double length, min_length;
  double main_diag[3];

  shortest = 0;
  mat_multiply_matrix_vector_di3(main_diag, rec_lattice, main_diagonals[0]);
  min_length = mat_norm_squared_d3(main_diag);
  for (i = 1; i < 4; i++) {
    mat_multiply_matrix_vector_di3(main_diag, rec_lattice, main_diagonals[i]);
    length = mat_norm_squared_d3(main_diag);
    if (min_length > length) {
      min_length = length;
      shortest = i;
    }
  }
  return shortest;
}

static double _f(const int n,
		 const int m,
		 const double omega,
		 const double vertices_omegas[4])
{
  return ((omega - vertices_omegas[m]) /
	  (vertices_omegas[n] - vertices_omegas[m]));
}

static double _J(const int i,
		 const int ci,
		 const double omega,
		 const double vertices_omegas[4])
{
  switch (i) {
  case 0:
    return _J_0();
  case 1:
    switch (ci) {
    case 0:
      return _J_10(omega, vertices_omegas);
    case 1:
      return _J_11(omega, vertices_omegas);
    case 2:
      return _J_12(omega, vertices_omegas);
    case 3:
      return _J_13(omega, vertices_omegas);
    }
  case 2:
    switch (ci) {
    case 0:
      return _J_20(omega, vertices_omegas);
    case 1:
      return _J_21(omega, vertices_omegas);
    case 2:
      return _J_22(omega, vertices_omegas);
    case 3:
      return _J_23(omega, vertices_omegas);
    }
  case 3:
    switch (ci) {
    case 0:
      return _J_30(omega, vertices_omegas);
    case 1:
      return _J_31(omega, vertices_omegas);
    case 2:
      return _J_32(omega, vertices_omegas);
    case 3:
      return _J_33(omega, vertices_omegas);
    }
  case 4:
    return _J_4();
  }

  warning_print("******* Warning *******\n");
  warning_print(" J is something wrong. \n");
  warning_print("******* Warning *******\n");
  warning_print("(line %d, %s).\n", __LINE__, __FILE__);

  return 0;
}


static double _I(const int i,
		 const int ci,
		 const double omega,
		 const double vertices_omegas[4])
{
  switch (i) {
  case 0:
    return _I_0();
  case 1:
    switch (ci) {
    case 0:
      return _I_10(omega, vertices_omegas);
    case 1:
      return _I_11(omega, vertices_omegas);
    case 2:
      return _I_12(omega, vertices_omegas);
    case 3:
      return _I_13(omega, vertices_omegas);
    }
  case 2:
    switch (ci) {
    case 0:
      return _I_20(omega, vertices_omegas);
    case 1:
      return _I_21(omega, vertices_omegas);
    case 2:
      return _I_22(omega, vertices_omegas);
    case 3:
      return _I_23(omega, vertices_omegas);
    }
  case 3:
    switch (ci) {
    case 0:
      return _I_30(omega, vertices_omegas);
    case 1:
      return _I_31(omega, vertices_omegas);
    case 2:
      return _I_32(omega, vertices_omegas);
    case 3:
      return _I_33(omega, vertices_omegas);
    }
  case 4:
    return _I_4();
  }

  warning_print("******* Warning *******\n");
  warning_print(" I is something wrong. \n");
  warning_print("******* Warning *******\n");
  warning_print("(line %d, %s).\n", __LINE__, __FILE__);

  return 0;
}

static double _n(const int i,
		 const double omega,
		 const double vertices_omegas[4])
{
  switch (i) {
  case 0:
    return _n_0();
  case 1:
    return _n_1(omega, vertices_omegas);
  case 2:
    return _n_2(omega, vertices_omegas);
  case 3:
    return _n_3(omega, vertices_omegas);
  case 4:
    return _n_4();
  }
  
  warning_print("******* Warning *******\n");
  warning_print(" n is something wrong. \n");
  warning_print("******* Warning *******\n");
  warning_print("(line %d, %s).\n", __LINE__, __FILE__);

  return 0;
}

static double _g(const int i,
		 const double omega,
		 const double vertices_omegas[4])
{
  switch (i) {
  case 0:
    return _g_0();
  case 1:
    return _g_1(omega, vertices_omegas);
  case 2:
    return _g_2(omega, vertices_omegas);
  case 3:
    return _g_3(omega, vertices_omegas);
  case 4:
    return _g_4();
  }
  
  warning_print("******* Warning *******\n");
  warning_print(" g is something wrong. \n");
  warning_print("******* Warning *******\n");
  warning_print("(line %d, %s).\n", __LINE__, __FILE__);

  return 0;
}

/* omega < omega1 */
static double _n_0(void)
{
  return 0.0;
}

/* omega1 < omega < omega2 */
static double _n_1(const double omega,
		   const double vertices_omegas[4])
{
  return (_f(1, 0, omega, vertices_omegas) *
	  _f(2, 0, omega, vertices_omegas) *
	  _f(3, 0, omega, vertices_omegas));
}

/* omega2 < omega < omega3 */
static double _n_2(const double omega,
		   const double vertices_omegas[4])
{
  return (_f(3, 1, omega, vertices_omegas) *
	  _f(2, 1, omega, vertices_omegas) +
	  _f(3, 0, omega, vertices_omegas) *
	  _f(1, 3, omega, vertices_omegas) *
	  _f(2, 1, omega, vertices_omegas) +
	  _f(3, 0, omega, vertices_omegas) *
	  _f(2, 0, omega, vertices_omegas) *
	  _f(1, 2, omega, vertices_omegas));
}
            
/* omega2 < omega < omega3 */
static double _n_3(const double omega,
		   const double vertices_omegas[4])
{
  return (1.0 -
	  _f(0, 3, omega, vertices_omegas) *
	  _f(1, 3, omega, vertices_omegas) *
	  _f(2, 3, omega, vertices_omegas));
}

/* omega4 < omega */
static double _n_4(void)
{
  return 1.0;
}

/* omega < omega1 */
static double _g_0(void)
{
  return 0.0;
}

/* omega1 < omega < omega2 */
static double _g_1(const double omega,
		   const double vertices_omegas[4])
{
  return (3 *
	  _f(1, 0, omega, vertices_omegas) *
	  _f(2, 0, omega, vertices_omegas) /
	  (vertices_omegas[3] - vertices_omegas[0]));
}

/* omega2 < omega < omega3 */
static double _g_2(const double omega,
		   const double vertices_omegas[4])
{
  return (3 /
	  (vertices_omegas[3] - vertices_omegas[0]) *
	  (_f(1, 2, omega, vertices_omegas) *
	   _f(2, 0, omega, vertices_omegas) +
	   _f(2, 1, omega, vertices_omegas) *
	   _f(1, 3, omega, vertices_omegas)));
}

/* omega3 < omega < omega4 */
static double _g_3(const double omega,
		   const double vertices_omegas[4])
{
    return (3 *
	    _f(1, 3, omega, vertices_omegas) *
	    _f(2, 3, omega, vertices_omegas) /
            (vertices_omegas[3] - vertices_omegas[0]));
}

/* omega4 < omega */
static double _g_4(void)
{
  return 0.0;
}

static double _J_0(void)
{
  return 0.0;
}

static double _J_10(const double omega,
		    const double vertices_omegas[4])
{
  return (1.0 +
	  _f(0, 1, omega, vertices_omegas) +
	  _f(0, 2, omega, vertices_omegas) +
	  _f(0, 3, omega, vertices_omegas)) / 4;
}

static double _J_11(const double omega,
		    const double vertices_omegas[4])
{
  return _f(1, 0, omega, vertices_omegas) / 4;
}

static double _J_12(const double omega,
		    const double vertices_omegas[4])
{
  return _f(2, 0, omega, vertices_omegas) / 4;
}

static double _J_13(const double omega,
		    const double vertices_omegas[4])
{
  return _f(3, 0, omega, vertices_omegas) / 4;
}

static double _J_20(const double omega,
		    const double vertices_omegas[4])
{
  return (_f(3, 1, omega, vertices_omegas) *
	  _f(2, 1, omega, vertices_omegas) +
	  _f(3, 0, omega, vertices_omegas) *
	  _f(1, 3, omega, vertices_omegas) *
	  _f(2, 1, omega, vertices_omegas) *
	  (1.0 +
	   _f(0, 3, omega, vertices_omegas)) +
	  _f(3, 0, omega, vertices_omegas) *
	  _f(2, 0, omega, vertices_omegas) *
	  _f(1, 2, omega, vertices_omegas) *
	  (1.0 +
	   _f(0, 3, omega, vertices_omegas) +
	   _f(0, 2, omega, vertices_omegas))) / 4 / _n_2(omega, vertices_omegas);
}

static double _J_21(const double omega,
		    const double vertices_omegas[4])
{
  return (_f(3, 1, omega, vertices_omegas) *
	  _f(2, 1, omega, vertices_omegas) *
	  (1.0 +
	   _f(1, 3, omega, vertices_omegas) +
	   _f(1, 2, omega, vertices_omegas)) +
	  _f(3, 0, omega, vertices_omegas) *
	  _f(1, 3, omega, vertices_omegas) *
	  _f(2, 1, omega, vertices_omegas) *
	  (_f(1, 3, omega, vertices_omegas) +
	   _f(1, 2, omega, vertices_omegas)) +
	  _f(3, 0, omega, vertices_omegas) *
	  _f(2, 0, omega, vertices_omegas) *
	  _f(1, 2, omega, vertices_omegas) *
	  _f(1, 2, omega, vertices_omegas)) / 4 / _n_2(omega, vertices_omegas);
}

static double _J_22(const double omega,
		    const double vertices_omegas[4])
{
  return (_f(3, 1, omega, vertices_omegas) *
	  _f(2, 1, omega, vertices_omegas) *
	  _f(2, 1, omega, vertices_omegas) +
	  _f(3, 0, omega, vertices_omegas) *
	  _f(1, 3, omega, vertices_omegas) *
	  _f(2, 1, omega, vertices_omegas) *
	  _f(2, 1, omega, vertices_omegas) +
	  _f(3, 0, omega, vertices_omegas) *
	  _f(2, 0, omega, vertices_omegas) *
	  _f(1, 2, omega, vertices_omegas) *
	  (_f(2, 1, omega, vertices_omegas) +
	   _f(2, 0, omega, vertices_omegas))) / 4 / _n_2(omega, vertices_omegas);
}

static double _J_23(const double omega,
		    const double vertices_omegas[4])
{
  return (_f(3, 1, omega, vertices_omegas) *
	  _f(2, 1, omega, vertices_omegas) *
	  _f(3, 1, omega, vertices_omegas) +
	  _f(3, 0, omega, vertices_omegas) *
	  _f(1, 3, omega, vertices_omegas) *
	  _f(2, 1, omega, vertices_omegas) *
	  (_f(3, 1, omega, vertices_omegas) +
	   _f(3, 0, omega, vertices_omegas)) +
	  _f(3, 0, omega, vertices_omegas) *
	  _f(2, 0, omega, vertices_omegas) *
	  _f(1, 2, omega, vertices_omegas) *
	  _f(3, 0, omega, vertices_omegas)) / 4 / _n_2(omega, vertices_omegas);
}

static double _J_30(const double omega,
		    const double vertices_omegas[4])
{
  return (1.0 -
	  _f(0, 3, omega, vertices_omegas) *
	  _f(0, 3, omega, vertices_omegas) *
	  _f(1, 3, omega, vertices_omegas) *
	  _f(2, 3, omega, vertices_omegas)) / 4 / _n_3(omega, vertices_omegas);
}

static double _J_31(const double omega,
		    const double vertices_omegas[4])
{
  return (1.0 -
	  _f(0, 3, omega, vertices_omegas) *
	  _f(1, 3, omega, vertices_omegas) *
	  _f(1, 3, omega, vertices_omegas) *
	  _f(2, 3, omega, vertices_omegas)) / 4 / _n_3(omega, vertices_omegas);
}

static double _J_32(const double omega,
		    const double vertices_omegas[4])
{
  return (1.0 +
	  _f(0, 3, omega, vertices_omegas) *
	  _f(1, 3, omega, vertices_omegas) *
	  _f(2, 3, omega, vertices_omegas) *
	  _f(2, 3, omega, vertices_omegas)) / 4 / _n_3(omega, vertices_omegas);
}

static double _J_33(const double omega,
		    const double vertices_omegas[4])
{
  return (1.0 -
	  _f(0, 3, omega, vertices_omegas) *
	  _f(1, 3, omega, vertices_omegas) *
	  _f(2, 3, omega, vertices_omegas) *
	  (1.0 +
	   _f(3, 0, omega, vertices_omegas) +
	   _f(3, 1, omega, vertices_omegas) +
	   _f(3, 2, omega, vertices_omegas))) / 4 / _n_3(omega, vertices_omegas);
}

static double _J_4(void)
{
  return 0.25;
}

static double _I_0(void)
{
  return 0.0;
}

static double _I_10(const double omega,
		    const double vertices_omegas[4])
{
  return (_f(0, 1, omega, vertices_omegas) +
	  _f(0, 2, omega, vertices_omegas) +
	  _f(0, 3, omega, vertices_omegas)) / 3;
}

static double _I_11(const double omega,
		    const double vertices_omegas[4])
{
  return _f(1, 0, omega, vertices_omegas) / 3;
}

static double _I_12(const double omega,
		    const double vertices_omegas[4])
{
  return _f(2, 0, omega, vertices_omegas) / 3;
}

static double _I_13(const double omega,
		    const double vertices_omegas[4])
{
  return _f(3, 0, omega, vertices_omegas) / 3;
}

static double _I_20(const double omega,
		    const double vertices_omegas[4])
{
  return (_f(0, 3, omega, vertices_omegas) +
	  _f(0, 2, omega, vertices_omegas) *
	  _f(2, 0, omega, vertices_omegas) *
	  _f(1, 2, omega, vertices_omegas) /
	  (_f(1, 2, omega, vertices_omegas) *
	   _f(2, 0, omega, vertices_omegas) +
	   _f(2, 1, omega, vertices_omegas) *
	   _f(1, 3, omega, vertices_omegas))) / 3;
}

static double _I_21(const double omega,
		    const double vertices_omegas[4])
{
  return (_f(1, 2, omega, vertices_omegas) +
	  _f(1, 3, omega, vertices_omegas) *
	  _f(1, 3, omega, vertices_omegas) *
	  _f(2, 1, omega, vertices_omegas) /
	  (_f(1, 2, omega, vertices_omegas) *
	   _f(2, 0, omega, vertices_omegas) +
	   _f(2, 1, omega, vertices_omegas) *
	   _f(1, 3, omega, vertices_omegas))) / 3;
}

static double _I_22(const double omega,
		    const double vertices_omegas[4])
{
  return (_f(2, 1, omega, vertices_omegas) +
	  _f(2, 0, omega, vertices_omegas) *
	  _f(2, 0, omega, vertices_omegas) *
	  _f(1, 2, omega, vertices_omegas) /
	  (_f(1, 2, omega, vertices_omegas) *
	   _f(2, 0, omega, vertices_omegas) +
	   _f(2, 1, omega, vertices_omegas) *
	   _f(1, 3, omega, vertices_omegas))) / 3;
}
            
static double _I_23(const double omega,
		    const double vertices_omegas[4])
{
  return (_f(3, 0, omega, vertices_omegas) +
	  _f(3, 1, omega, vertices_omegas) *
	  _f(1, 3, omega, vertices_omegas) *
	  _f(2, 1, omega, vertices_omegas) /
	  (_f(1, 2, omega, vertices_omegas) *
	   _f(2, 0, omega, vertices_omegas) +
	   _f(2, 1, omega, vertices_omegas) *
	   _f(1, 3, omega, vertices_omegas))) / 3;
}

static double _I_30(const double omega,
		    const double vertices_omegas[4])
{
  return _f(0, 3, omega, vertices_omegas) / 3;
}

static double _I_31(const double omega,
		    const double vertices_omegas[4])
{
  return _f(1, 3, omega, vertices_omegas) / 3;
}

static double _I_32(const double omega,
		    const double vertices_omegas[4])
{
  return _f(2, 3, omega, vertices_omegas) / 3;
}

static double _I_33(const double omega,
		    const double vertices_omegas[4])
{
  return (_f(3, 0, omega, vertices_omegas) +
	  _f(3, 1, omega, vertices_omegas) +
	  _f(3, 2, omega, vertices_omegas)) / 3;
}

static double _I_4(void)
{
  return 0.0;
}