/*
   Copyright (c) 2009-2015, Jack Poulson
   All rights reserved.

   This file is part of Elemental and is under the BSD 2-Clause License, 
   which can be found in the LICENSE file in the root directory, or at 
   http://opensource.org/licenses/BSD-2-Clause
*/
#include "El.hpp"
#include "../util.hpp"

namespace El {
namespace socp {
namespace affine {

// The full KKT system is of the form
//
//   | 0 A^T      G     | | x |   |        -c             |
//   | A 0        0     | | y |   |         b             |,
//   | G 0    -(z <> s) | | z | = | -z <> (s o z + tau e) |
//
// and the particular system solved is of the form
//
//   | 0 A^T      G     | | dx |   |     -rc        |
//   | A 0        0     | | dy |   |     -rb        |,
//   | G 0    -(z <> s) | | dz | = | -rh + z <> rmu |
//
// where 
//
//   rc  = A^T y + G^T z + c,
//   rb  = A x - b,
//   rh  = G x + s - h,
//   rmu = s o z - tau e.
//
// However, a large amount of fill-in is incurred if member cones are large,
// as the the linear operator implied by -(z <> s) is block-diagonal, with
// each diagonal block corresponding to a member cone. Thankfully, this matrix
// is known [citations!] to be a symmetric rank-two correction to a 
// definite diagonal matrix, and so a sparse embedding can be applied.

template<typename Real>
void KKT
( const Matrix<Real>& A, 
  const Matrix<Real>& G,
  const Matrix<Real>& s, 
  const Matrix<Real>& z,
  const Matrix<Int>& orders,
  const Matrix<Int>& firstInds,
        Matrix<Real>& J, bool onlyLower )
{
    DEBUG_ONLY(CSE cse("socp::affine::KKT"))
    LogicError("This routine is not yet finished");
    /*
    const Int m = A.Height();
    const Int n = A.Width();
    const Int k = G.Height();

    Zeros( J, n+m+k, n+m+k );
    const IR xInd(0,n), yInd(n,n+m), zInd(n+m,n+m+k);
    auto Jxx = J(xInd,xInd); auto Jxy = J(xInd,yInd); auto Jxz = J(xInd,zInd); 
    auto Jyx = J(yInd,xInd); auto Jyy = J(yInd,yInd); auto Jyz = J(yInd,zInd); 
    auto Jzx = J(zInd,xInd); auto Jzy = J(zInd,yInd); auto Jzz = J(zInd,zInd); 

    // Jyx := A
    // ========
    Jyx = A;

    // Jzx := G
    // ========
    Jzx = G;

    // Jzz := - z <> s
    // ===============
    Matrix<Real> t;
    t = s;
    DiagonalSolve( LEFT, NORMAL, z, t );
    Scale( Real(-1), t );
    Diagonal( Jzz, t );

    if( !onlyLower )
    {
        // Jxy := A^T
        // ==========
        Transpose( A, Jxy ); 

        // Jxz := G^T
        // ==========
        Transpose( G, Jxz );
    }
    */
}

template<typename Real>
void KKT
( const AbstractDistMatrix<Real>& A,    
  const AbstractDistMatrix<Real>& G,
  const AbstractDistMatrix<Real>& sPre, 
  const AbstractDistMatrix<Real>& zPre,
  const AbstractDistMatrix<Int>& ordersPre,
  const AbstractDistMatrix<Int>& firstIndsPre,
        AbstractDistMatrix<Real>& JPre, bool onlyLower )
{
    DEBUG_ONLY(CSE cse("socp::affine::KKT"))
    LogicError("This routine is not yet finished");
    /*
    const Int m = A.Height();
    const Int n = A.Width();
    const Int k = G.Height();

    auto sPtr = ReadProxy<Real,STAR,STAR>(&sPre); auto& s = *sPtr;
    auto zPtr = ReadProxy<Real,STAR,STAR>(&zPre); auto& z = *zPtr;
    auto JPtr = WriteProxy<Real,MC,MR>(&JPre);    auto& J = *JPtr;

    Zeros( J, n+m+k, n+m+k );
    const IR xInd(0,n), yInd(n,n+m), zInd(n+m,n+m+k);
    auto Jxx = J(xInd,xInd); auto Jxy = J(xInd,yInd); auto Jxz = J(xInd,zInd);
    auto Jyx = J(yInd,xInd); auto Jyy = J(yInd,yInd); auto Jyz = J(yInd,zInd);
    auto Jzx = J(zInd,xInd); auto Jzy = J(zInd,yInd); auto Jzz = J(zInd,zInd);

    // Jyx := A
    // ========
    Jyx = A;

    // Jzx := G
    // ========
    Jzx = G;

    // Jzz := - z <> s
    // ===============
    DistMatrix<Real,MC,STAR> t(s.Grid());
    t = s;
    DiagonalSolve( LEFT, NORMAL, z, t );
    Scale( Real(-1), t );
    Diagonal( Jzz, t );

    if( !onlyLower )
    {
        // Jxy := A^T
        // ==========
        Transpose( A, Jxy );

        // Jxz := G
        // ========
        Transpose( G, Jxz );
    }
    */
}

template<typename Real>
void KKT
( const SparseMatrix<Real>& A, 
  const SparseMatrix<Real>& G,
  const Matrix<Real>& s, 
  const Matrix<Real>& z,
  const Matrix<Int>& orders,
  const Matrix<Int>& firstInds,
        SparseMatrix<Real>& J, bool onlyLower )
{
    DEBUG_ONLY(CSE cse("socp::affine::KKT"))
    LogicError("This routine is not yet finished");
    /*
    const Int n = A.Width();
    SparseMatrix<Real> Q;
    Q.Resize( n, n );
    qp::affine::KKT( Q, A, G, s, z, J, onlyLower );
    */
}

template<typename Real>
void KKT
( const DistSparseMatrix<Real>& A, 
  const DistSparseMatrix<Real>& G,
  const DistMultiVec<Real>& s,     
  const DistMultiVec<Real>& z,
  const DistMultiVec<Int>& orders,
  const DistMultiVec<Int>& firstInds,
        DistSparseMatrix<Real>& J, bool onlyLower )
{
    DEBUG_ONLY(CSE cse("socp::affine::KKT"))
    LogicError("This routine is not yet finished");
    /*
    const Int n = A.Width();
    mpi::Comm comm = A.Comm();
    DistSparseMatrix<Real> Q(comm);
    Q.Resize( n, n );
    qp::affine::KKT( Q, A, G, s, z, J, onlyLower );
    */
}

#define PROTO(Real) \
  template void KKT \
  ( const Matrix<Real>& A, \
    const Matrix<Real>& G, \
    const Matrix<Real>& s, \
    const Matrix<Real>& z, \
    const Matrix<Int>& orders, \
    const Matrix<Int>& firstInds, \
          Matrix<Real>& J, bool onlyLower ); \
  template void KKT \
  ( const AbstractDistMatrix<Real>& A, \
    const AbstractDistMatrix<Real>& G, \
    const AbstractDistMatrix<Real>& s, \
    const AbstractDistMatrix<Real>& z, \
    const AbstractDistMatrix<Int>& orders, \
    const AbstractDistMatrix<Int>& firstInds, \
          AbstractDistMatrix<Real>& J, bool onlyLower ); \
  template void KKT \
  ( const SparseMatrix<Real>& A, \
    const SparseMatrix<Real>& G, \
    const Matrix<Real>& s, \
    const Matrix<Real>& z, \
    const Matrix<Int>& orders, \
    const Matrix<Int>& firstInds, \
          SparseMatrix<Real>& J, bool onlyLower ); \
  template void KKT \
  ( const DistSparseMatrix<Real>& A, \
    const DistSparseMatrix<Real>& G, \
    const DistMultiVec<Real>& s, \
    const DistMultiVec<Real>& z, \
    const DistMultiVec<Int>& orders, \
    const DistMultiVec<Int>& firstInds, \
          DistSparseMatrix<Real>& J, bool onlyLower );

#define EL_NO_INT_PROTO
#define EL_NO_COMPLEX_PROTO
#include "El/macros/Instantiate.h"

} // namespace affine
} // namespace socp
} // namespace El