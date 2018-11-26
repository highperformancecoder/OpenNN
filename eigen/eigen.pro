TEMPLATE = lib
  TARGET = eigen
  
# TODO port OpenNN to standalone eigen library
HEADERS = ../eigen/Cholesky  \
    ../eigen/IterativeLinearSolvers \
    ../eigen/QtAlignedMalloc \
    ../eigen/StdDeque \
    ../eigen/CholmodSupport \
    ../eigen/Jacobi \
    ../eigen/Sparse \
    ../eigen/StdList \
    ../eigen/Core \
    ../eigen/LU \
    ../eigen/SparseCholesky \
    ../eigen/StdVector \
    ../eigen/Dense \
    ../eigen/MetisSupport \
    ../eigen/SparseCore \
    ../eigen/SuperLUSupport \
    ../eigen/Eigen \
    ../eigen/OrderingMethods \
    ../eigen/SparseLU \
    ../eigen/SVD \
    ../eigen/Eigenvalues \
    ../eigen/PardisoSupport \
    ../eigen/SparseQR \
    ../eigen/UmfPackSupport \
    ../eigen/Geometry \
    ../eigen/PaStiXSupport \
    ../eigen/SPQRSupport \
    ../eigen/Householder \
    ../eigen/QR
    
isEmpty(PREFIX) {PREFIX=/usr/local}
headers.files=$$HEADERS
headers.path=$$PREFIX/include/eigen
INSTALLS += headers

# header only library
