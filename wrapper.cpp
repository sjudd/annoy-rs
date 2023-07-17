#include <stddef.h>
#include "annoy/src/kissrandom.h"
#include "annoy/src/annoylib.h"
#include "wrapper.hpp"

using namespace Annoy;

typedef ::AnnoyIndex<uint32_t, float, ::Angular, ::Kiss64Random, AnnoyIndexSingleThreadedBuildPolicy> AngularIndex;

extern "C"
{
    void *annoy_angular_create_index(int f)
    {
        AngularIndex *ptr = new AngularIndex(f);
        return (void *)ptr;
    }

    bool annoy_angular_add_item(void *idx, int item, float *w, char **error)
    {
        auto ptr = (AngularIndex *)idx;
        return ptr->add_item(item, w, error);
    }

    bool annoy_angular_build(void *idx, int q, int n_threads, char **error)
    {
        auto ptr = (AngularIndex *)idx;
        return ptr->build(q, n_threads, error);
    }

    bool annoy_angular_unbuild(void *idx, char **error)
    {
        auto ptr = (AngularIndex *)idx;
        return ptr->unbuild(error);
    }

    bool annoy_angular_save(void *idx, char *filename, bool prefault, char **error)
    {
        auto ptr = (AngularIndex *)idx;
        return ptr->save(filename, prefault, error);
    }

    void annoy_angular_unload(void *idx)
    {
        auto ptr = (AngularIndex *)idx;
        ptr->unload();
    }

    bool annoy_angular_load(void *idx, char *filename, bool prefault, char **error)
    {
        auto ptr = (AngularIndex *)idx;
        return ptr->load(filename, prefault, error);
    }

    float annoy_angular_get_distance(void *idx, uint32_t i, uint32_t j)
    {
        auto ptr = (AngularIndex *)idx;
        return ptr->get_distance(i, j);
    }

    void annoy_angular_get_nns_by_item(void *idx, uint32_t item, size_t n, int search_k, uint32_t *result, float *distances)
    {
        auto ptr = (AngularIndex *)idx;
        std::vector<uint32_t> resultVector;
        std::vector<float> distancesVector;
        ptr->get_nns_by_item(item, n, search_k, &resultVector, &distancesVector);
        for (auto i = 0; i < resultVector.size(); i++)
        {
            result[i] = resultVector[i];
            distances[i] = distancesVector[i];
        }
    }

    void annoy_angular_get_nns_by_vector(void *idx, float *w, size_t n, int search_k, uint32_t *result, float *distances)
    {
        auto ptr = (AngularIndex *)idx;
        std::vector<uint32_t> resultVector;
        std::vector<float> distancesVector;
        ptr->get_nns_by_vector(w, n, search_k, &resultVector, &distancesVector);
        for (auto i = 0; i < resultVector.size(); i++)
        {
            result[i] = resultVector[i];
            distances[i] = distancesVector[i];
        }
    }

    uint32_t annoy_angular_get_n_items(void *idx)
    {
        auto ptr = (AngularIndex *)idx;
        return ptr->get_n_items();
    }

    void annoy_angular_verbose(void *idx, bool v)
    {
        auto ptr = (AngularIndex *)idx;
        ptr->verbose(v);
    }

    void annoy_angular_get_item(void *idx, uint32_t item, float *v)
    {
        auto ptr = (AngularIndex *)idx;
        ptr->get_item(item, v);
    }

    void annoy_angular_set_seed(void *idx, uint64_t q)
    {
        auto ptr = (AngularIndex *)idx;
        ptr->set_seed(q);
    }

    bool annoy_angular_on_disk_build(void *idx, char *filename, char **error)
    {
        auto ptr = (AngularIndex *)idx;
        return ptr->on_disk_build(filename, error);
    }

    void annoy_angular_free_index(void *idx)
    {
        delete (AngularIndex *)idx;
    }

    void annoy_angular_free_error(char *error)
    {
        free(error);
    }
}