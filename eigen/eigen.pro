TEMPLATE = lib
  TARGET = eigen
  
# TODO port OpenNN to standalone eigen library
HEADERS = ../eigen/Cholesky  \
    IterativeLinearSolvers \
    QtAlignedMalloc \
    StdDeque \
    CholmodSupport \
    Jacobi \
    Sparse \
    StdList \
    Core \
    LU \
    SparseCholesky \
    StdVector \
    Dense \
    MetisSupport \
    SparseCore \
    SuperLUSupport \
    Eigen \
    OrderingMethods \
    SparseLU \
    SVD \
    Eigenvalues \
    PardisoSupport \
    SparseQR \
    UmfPackSupport \
    Geometry \
    PaStiXSupport \
    SPQRSupport \
    Householder \
    QR
    
isEmpty(PREFIX) {PREFIX=/usr/local}
headers.files=$$HEADERS src
headers.path=$$PREFIX/include/eigen
INSTALLS += headers

# header only library
