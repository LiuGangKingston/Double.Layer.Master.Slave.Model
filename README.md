# Double.Layer.Master.Slave.Model

Recent years have seen the growing availability of multi-node clusters with multi-core nodes. For such clusters a "hybrid approach" suggests itself. This approach combines message passing using MPI with multithreading using OpenMP to achieve optimal utilization of these resources.

Double layer master slave model is a combination of the MPI master slave model and the OpenMP all-slave model. For many independent but uneven jobs, the model groups the jobs into groups. Each job group is sent to a shared-memory node via MPI master slave model, then completed by the OpenMP all slave model. This library also allows users to send initial data for each job group and collect completed results dynamically. This model can also regard an existing OpenMP or MPI parallel code as a single job then cast an additional outer layer parallelism.

Please cite "A Hybrid Double-Layer Master-Slave Model For Multicore-Node Clusters", 
Liu, Gang; Schmider, Hartmut; Edgecombe, Kenneth E, 
HIGH PERFORMANCE COMPUTING SYMPOSIUM 2012 (HPCS2012), 
Journal of Physics Conference Series, Volume: 385, Article Number: 012011, Published: 2012 
