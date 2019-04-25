import numpy as np
import scipy as sp
import scipy.sparse


def map_bytes_to_dtype(nbytes, int_type=False):
    # Should use a dict instead
    if (nbytes == 4) and (not int_type):
        return 'float32'
    elif (nbytes == 8) and (not int_type):
        return 'float64'
    elif (nbytes == 4) and int_type:
        return 'int32'
    elif (nbytes == 8) and int_type:
        return 'int64'
    else:
        raise ValueError('nbytes must be 4 or 8 but {0} passed to function'.format(nbytes))


def import_full_c(filename):
    with open(filename, 'r') as fid:
        nbytes = int(np.fromfile(fid, dtype=np.int32, count=1))
        m = int(np.fromfile(fid, dtype=np.int32, count=1))
        n = int(np.fromfile(fid, dtype=np.int32, count=1))

        x = reshape(np.fromfile(fid,
                                dtype=map_bytes_to_dtype(nbytes)),
                    (m, n),
                    order='F')

        return x


def import_full_r(filename):
    with open(filename, 'r') as fid:
        nbytes = int(np.fromfile(fid, dtype=np.int32, count=1))
        m = int(np.fromfile(fid, dtype=np.int32, count=1))
        n = int(np.fromfile(fid, dtype=np.int32, count=1))

        x = np.fromfile(fid, dtype=map_bytes_to_dtype(nbytes))
        x.shape = (m, n)
        return x


def import_vector(filename):
    with open(filename, 'r') as fid:
        nbytes = int(np.fromfile(fid, dtype=np.int32, count=1))
        n = int(np.fromfile(fid, dtype=np.int32, count=1))

        x = np.fromfile(fid, dtype=map_bytes_to_dtype(nbytes))
        assert(len(x) == n)
        return x


def import_ivector(filename):
    with open(filename, 'r') as fid:
        nbytes = int(np.fromfile(fid, dtype=np.int32, count=1))
        n = int(np.fromfile(fid, dtype=np.int32, count=1))

        x = np.fromfile(fid, dtype=map_bytes_to_dtype(nbytes, int_type=True))
        assert(len(x) == n)
        return x


def import_rcs(filename):
    with open(filename, 'r') as fid:
        nbytes = int(np.fromfile(fid, dtype=np.int32, count=1))
        m = int(np.fromfile(fid, dtype=np.int32, count=1))
        n = int(np.fromfile(fid, dtype=np.int32, count=1))
        N = int(np.fromfile(fid, dtype=np.int32, count=1))

        v = np.fromfile(fid, dtype=map_bytes_to_dtype(nbytes), count=N)
        j = np.fromfile(fid, dtype=np.int32, count=N)
        r = np.fromfile(fid, dtype=np.int32, count=m+1)

        return sp.sparse.csr_matrix((v, j, r), shape=(m, n))


def import_diag(filename):
    with open(filename, 'r') as fid:
        nbytes = int(np.fromfile(fid, dtype=np.int32, count=1))
        m = int(np.fromfile(fid, dtype=np.int32, count=1))
        n = int(np.fromfile(fid, dtype=np.int32, count=1))
        v = np.fromfile(fid, dtype=map_bytes_to_dtype(nbytes), count=min(m,n))

        return sp.sparse.spdiags(v, 0, m, n)


################################################################################


def export_full_r(filename, x, dtype=np.double):
    with open(filename, 'w') as fid:
        m, n = x.shape

        z = np.array([numpy.dtype(dtype).itemsize], dtype='int32')
        z.tofile(fid)

        z = np.array([m, n], dtype='int32')
        z.tofile(fid)

        if (x.dtype != dtype):
            x_dtype = np.array(x, dtype=dtype)
            x_dtype.tofile(fid)
        else:
            x.tofile(fid)


def export_vector(filename, x, dtype=np.double):
    with open(filename, 'w') as fid:
        n = len(x)

        z = np.array([numpy.dtype(dtype).itemsize], dtype='int32')
        z.tofile(fid)

        z = np.array([n], dtype='int32')
        z.tofile(fid)

        if (x.dtype != dtype):
            x_dtype = np.array(x, dtype=dtype)
            x_dtype.tofile(fid)
        else:
            x.tofile(fid)


def export_ivector(filename, x, dtype=np.int64):
    export_vector(filename, np.asarray(x, dtype=dtype), dtype=dtype)


def export_rcs(filename, A, dtype=np.double):
    with open(filename, 'w') as fid:
        A = csr_matrix(A, dtype=dtype)

        m, n = A.shape
        N = A.nnz

        v = A.data
        j = A.indices
        r = A.indptr

        z = np.array([numpy.dtype(dtype).itemsize, m, n, N], dtype='int32')
        z.tofile(fid)

        assert(j.dtype == 'int32')
        assert(r.dtype == 'int32')

        v.tofile(fid)
        j.tofile(fid)
        r.tofile(fid)


def export_diag(filename, A, dtype=np.double):
    with open(filename, 'w') as fid:
        m, n = A.shape
        v = np.asarray(A.diagonal(), dtype=dtype)

        z = np.array([numpy.dtype(dtype).itemsize, m, n], dtype=int32)
        z.tofile(fid)

        v.tofile(fid)


def export_r_filter_new(filename, H, dtype=np.double):
    with open(filename, 'w') as fid:
        header = np.array([numpy.dtype(dtype).itemsize, H.ndim], dtype='int32')
        n_log = np.array(H.shape, dtype='int32')
        header.tofile(fid)
        n_log.tofile(fid)

        H_dtype = np.asarray(H, dtype=dtype)
        H_dtype.tofile(fid)


def export_sb_toe_r(filename, blocks, dtype=np.double):
    rank = len(blocks.shape)

    n = blocks.shape

    n_phy = []
    for dim in range(rank):
        index = [slice(None)] * rank
        count = 0
        for i in range(n[dim]):
            index[dim] = slice(i, i+1)
            if any(blocks[tuple(index)].flat):
                count += 1
        n_phy.append(count)

    with open(filename, 'w') as fid:
        z = np.array([np.dtype(dtype).itemsize], dtype='int32')
        z.tofile(fid)

        z = np.array([rank], dtype='int32')
        z.tofile(fid)

        z = np.array(n_phy[::-1], dtype='int32')
        z.tofile(fid)

        z = np.array(n[::-1], dtype='int32')
        z.tofile(fid)

        index = tuple(slice(None, x) for x in n_phy)
        blocks_phy = blocks[index]

        z = np.array(blocks_phy.reshape((np.prod(n_phy),),
                                        order='F'), dtype=dtype)
        z.tofile(fid)

    return filename
