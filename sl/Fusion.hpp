/*
 * SOFTWARE LICENSE
 * BY USING YOUR CAMERA YOU AGREE TO THIS SOFTWARE LICENSE. BEFORE SETTING IT UP,
 * PLEASE READ THIS SOFTWARE LICENSE CAREFULLY. IF YOU DO NOT ACCEPT THIS
 * SOFTWARE LICENSE, DO NOT USE YOUR CAMERA. RETURN IT TO UNUSED TO STEREOLABS
 * FOR A REFUND. Contact STEREOLABS at support@stereolabs.com
 *
 * 1. Definitions
 *
 * "Authorized Accessory" means a STEREOLABS branded ZED, ZED 2, ZED Mini, ZED X, and a STEREOLABS
 * licensed, third party branded, ZED hardware accessory whose packaging bears the official
 * "Licensed for ZED" logo. The ZED, ZED 2, ZED Mini, ZED X camera are Authorized Accessories
 * solely for purpose of this Software license.
 * "Software" means the Software Development Kit, available on the stereolabs.com website, and including any updates STEREOLABS may make available from
 * time to time.
 * "Unauthorized Accessories" means all hardware accessories other than an Authorized Accessory.
 * "Unauthorized Software" means any software not distributed by STEREOLABS.
 * "You" means the user of a ZED, ZED 2, ZED Mini, ZED X camera.
 *
 * 2. License
 *
 * a. The Software is licensed to You, not sold. You are licensed to use the
 * Software only as downloaded from the stereolabs.com website, and updated by
 * STEREOLABS from time to time. You may not copy or reverse engineer the Software.
 *
 * b. As conditions to this Software license, You agree that:
 *   i. You will use Your Software with ZED, ZED 2, ZED Mini, ZED X camera only and not with any
 *      other device (including). You will not use Unauthorized Accessories. They may
 *      not work or may stop working permanently after a Software update.
 *   ii. You will not use or install any Unauthorized Software with an Authorized Accessory. If You do, Your ZED, ZED 2,
 *      ZED Mini, ZED X camera may stop working permanently at that time or after a later
 *       Software update.
 *   iii. You will not attempt to defeat or circumvent any Software technical limitation,
 *        security, or anti-piracy system. If You do, Your ZED, ZED 2, ZED Mini, ZED X camera may stop
 *        working permanently at that time or after a later Software update.
 *   iv. STEREOLABS may use technical measures, including Software updates, to limit use
 *       of the Software to the ZED, ZED 2, ZED Mini, ZED X camera, to prevent use of Unauthorized
 *       Accessories, and to protect the technical limitations, security and anti-piracy
 *       systems in the ZED, ZED 2, ZED Mini, ZED X camera.
 *   v. STEREOLABS may update the Software from time to time without further notice to You,
 *      for example, to update any technical limitation, security, or anti-piracy system.
 *
 * 3. Warranty
 *
 * The Software is covered by the Limited Warranty for Your ZED, ZED 2, ZED Mini, ZED X camera, and
 * STEREOLABS gives no other guarantee, warranty, or condition for the Software. No one
 * else may give any guarantee, warranty, or condition on STEREOLABS's behalf.
 *
 * 4. EXCLUSION OF CERTAIN DAMAGES
 *
 * STEREOLABS IS NOT RESPONSIBLE FOR ANY INDIRECT, INCIDENTAL, SPECIAL, OR CONSEQUENTIAL
 * DAMAGES; ANY LOSS OF DATA, PRIVACY, CONFIDENTIALITY, OR PROFITS; OR ANY INABILITY TO
 * USE THE SOFTWARE. THESE EXCLUSIONS APPLY EVEN IF STEREOLABS HAS BEEN ADVISED OF THE
 * POSSIBILITY OF THESE DAMAGES, AND EVEN IF ANY REMEDY FAILS OF ITS ESSENTIAL PURPOSE.
 *
 * 5. Choice of Law
 *
 * French law governs the interpretation of this Software license and any claim that
 * STEREOLABS has breached it, regardless of conflict of law principles.
 *
 */

#ifndef __FUSION_HPP__
#define __FUSION_HPP__

#include <sl/Camera.hpp>

#pragma message("~ FUSION SDK is distributed in Early Access ~")

// Stereolabs namespace
namespace sl {

    /**
      \class FusionConfiguration
      \ingroup Fusion_group
      \brief useful struct to store the Fusion configuration, can be read from /write to a Json file.
     */
    struct FusionConfiguration {
        /**
        \brief The serial number of the used ZED camera.
         */
        int serial_number;

        /**
        \brief The communication parameters to connect this camera to the Fusion
         */
        CommunicationParameters communication_parameters;

        /**
        \brief The WORLD Pose of the camera for Fusion
         */
        Transform pose;

        /**
        \brief The input type for the current camera.
         */
        InputType input_type;
    };

    /**
    \ingroup Fusion_group
    \brief Read a Configuration JSON file to configure a fusion process 
    \param json_config_filename : The name of the JSON file containing the configuration
    \param serial_number : the serial number of the ZED Camera you want to retrieve
    \param coord_sys : the COORDINATE_SYSTEM in which you want the World Pose to be in
    \param unit : the UNIT in which you want the World Pose to be in

    \return a \ref FusionConfiguration for the requested camera
    \note empty if no data were found for the requested camera
     */
    FusionConfiguration /*@cond SHOWHIDDEN*/SL_CORE_EXPORT/*@endcond*/ readFusionConfigurationFile(std::string json_config_filename, int serial_number, sl::COORDINATE_SYSTEM coord_sys, sl::UNIT unit);

    /**
    \ingroup Fusion_group
    \brief Read a Configuration JSON file to configure a fusion process 
    \param json_config_filename : The name of the JSON file containing the configuration
    \param coord_sys : the COORDINATE_SYSTEM in which you want the World Pose to be in
    \param unit : the UNIT in which you want the World Pose to be in

    \return a vector of \ref FusionConfiguration for all the camera present in the file
    \note empty if no data were found for the requested camera
     */
    std::vector<FusionConfiguration> /*@cond SHOWHIDDEN*/SL_CORE_EXPORT/*@endcond*/ readFusionConfigurationFile(std::string json_config_filename, sl::COORDINATE_SYSTEM coord_sys, sl::UNIT unit);

    /**
    \ingroup Fusion_group
    \brief Write a Configuration JSON file to configure a fusion process 
    \param json_config_filename : The name of the JSON that will contain the information
    \param conf: a vector of \ref FusionConfiguration listing all the camera configurations
    \param coord_sys : the COORDINATE_SYSTEM in which the World Pose is
    \param unit : the UNIT in which the World Pose is
     */
    void /*@cond SHOWHIDDEN*/SL_CORE_EXPORT/*@endcond*/ writeConfigurationFile(std::string json_config_filename, std::vector<FusionConfiguration> &configuration, sl::COORDINATE_SYSTEM coord_sys, sl::UNIT unit);

    /**
    \class InitFusionParameters
    \ingroup Fusion_group
    \brief Holds the options used to initialize the \ref Fusion object.
     */
    struct /*@cond SHOWHIDDEN*/SL_CORE_EXPORT/*@endcond*/ InitFusionParameters {
        /**
        This parameter allows you to select the unit to be used for all metric values of the SDK. (depth, point cloud, tracking, mesh, and others).
        \n default : \ref UNIT "UNIT::MILLIMETER"
         */
        UNIT coordinate_units;

        /**
        Positional tracking, point clouds and many other features require a given \ref COORDINATE_SYSTEM to be used as reference.
        This parameter allows you to select the \ref COORDINATE_SYSTEM used by the \ref Camera to return its measures.
        \n This defines the order and the direction of the axis of the coordinate system.
        \n default : \ref COORDINATE_SYSTEM "COORDINATE_SYSTEM::IMAGE"
         */
        COORDINATE_SYSTEM coordinate_system;

        /**
         * @brief It allows users to extract some stats of the Fusion API like drop frame of each camera, latency, etc
         * 
         */
        bool output_performance_metrics;

        /**
          Enable the verbosity mode of the SDK
         */
        bool verbose;

        /**
         * @brief If specified change the number of period necessary for a source to go in timeout without data. For example, if you set this to 5
         * then, if any source do not receive data during 5 period, these sources will go to timeout and will be ignored.
         */
        unsigned timeout_period_number;

        /**
         * @brief Default constructor
         */
        InitFusionParameters(
                UNIT coordinate_units_ = UNIT::MILLIMETER,
                COORDINATE_SYSTEM coordinate_system_ = COORDINATE_SYSTEM::IMAGE,
                bool output_performance_metrics = true,
                bool verbose_ = false,
                unsigned timeout_period_number = 20);
    };

    /**
    \class CameraIdentifier
    \ingroup Fusion_group
    \brief Used to identify a specific camera in the Fusion API
     */
    struct /*@cond SHOWHIDDEN*/SL_CORE_EXPORT/*@endcond*/ CameraIdentifier {

        CameraIdentifier() : sn(0) {
        }

        CameraIdentifier(uint64_t sn_) : sn(sn_) {
        }
        uint64_t sn;
    };

    /*@cond SHOWHIDDEN*/
    inline bool operator<(const sl::CameraIdentifier &a, const sl::CameraIdentifier &b) {
        return a.sn < b.sn;
    }
    /*@endcond*/

    /**
    \enum FUSION_ERROR_CODE
    \ingroup Fusion_group
    \brief Lists the types of error that can be raised by the Fusion.
     */
    enum class FUSION_ERROR_CODE {
        WRONG_BODY_FORMAT = -7, /**< Senders use different body format, consider to change them.*/
        NOT_ENABLE = -6, /**< The following module was not enabled.*/
        INPUT_FEED_MISMATCH = -5, /**< Some source are provided by SVO and some sources are provided by LIVE stream. */
        CONNECTION_TIMED_OUT = -4, /**< Connection timed out, impossible to reach the sender, verify the ip/port of the sender. */
        MEMORY_ALREADY_USED = -3, /**< intra process shared memory allocation issue, multiple connection to the same data. */
        BAD_IP_ADDRESS = -2, /**< The IP format provided is wrong, please provide IP in this format a.b.c.d where (a, b, c, d) are numbers between 0 and 255.*/
        FAILURE = -1, /**< Standard code for unsuccessful behavior.*/
        SUCCESS = 0,
        FUSION_ERRATIC_FPS = 1, /**< Some big differences has been observed between senders FPS. */
        FUSION_FPS_TOO_LOW = 2 /**< At least one sender has fps lower than 10 FPS. */
    };

    ///@cond SHOWHIDDEN
    String SL_CORE_EXPORT toString(const FUSION_ERROR_CODE &state);

    inline std::ostream &operator<<(std::ostream &os, const FUSION_ERROR_CODE &state) {
        return os << toString(state);
    }
    ///@endcond

    /**
    \enum SENDER_ERROR_CODE
    \ingroup Fusion_group
    \brief Lists the types of error that can be raised during the Fusion by senders
     */
    enum class SENDER_ERROR_CODE {
        DISCONNECTED = -1, /**< the sender has been disconnected*/
        SUCCESS = 0,
        GRAB_ERROR = 1, /**< the sender has encountered an grab error*/
        ERRATIC_FPS = 2, /**< the sender does not run with a constant frame rate*/
        FPS_TOO_LOW = 3 /**< fps lower than 10 FPS*/
    };

    ///@cond SHOWHIDDEN
    String SL_CORE_EXPORT toString(const SENDER_ERROR_CODE &state);

    inline std::ostream &operator<<(std::ostream &os, const SENDER_ERROR_CODE &state) {
        return os << toString(state);
    }
    ///@endcond

    /**
    \class BodyTrackingFusionParameters
    \ingroup Fusion_group
    \brief Holds the options used to initialize the body tracking module of the \ref Fusion.
     */
    struct /*@cond SHOWHIDDEN*/SL_CORE_EXPORT/*@endcond*/ BodyTrackingFusionParameters {
                
         /**
        \brief Defines if the object detection will track objects across images flow
         */
        bool enable_tracking = true;

        /**
        \brief Defines if the body fitting will be applied
        \note If you enable it and the camera provides data as BODY_18 the fused body format will be BODY_34.
         */
        bool enable_body_fitting = false;
    };

    /**
    \class BodyTrackingFusionRuntimeParameters
    \ingroup Fusion_group
    \brief Holds the options used to change the behavior of the body tracking module at runtime.
     */
    struct /*@cond SHOWHIDDEN*/SL_CORE_EXPORT/*@endcond*/ BodyTrackingFusionRuntimeParameters {
        /**
         * @brief if the fused skeleton has less than skeleton_minimum_allowed_keypoints keypoints, it will be discarded
         * 
         */
        int skeleton_minimum_allowed_keypoints = -1;

        /**
         * @brief if a skeleton was detected in less than skeleton_minimum_allowed_camera cameras, it will be discarded
         *
         */
        int skeleton_minimum_allowed_camera = -1;

        /**
         * @brief this value controls the smoothing of the tracked or fitted fused skeleton.
         * it is ranged from 0 (low smoothing) and 1 (high smoothing)
         */
        float skeleton_smoothing = 0.f;
    };

    struct /*@cond SHOWHIDDEN*/SL_CORE_EXPORT/*@endcond*/ PositionalTrackingFusionParameters {
        PositionalTrackingFusionParameters();
        /**
         * @brief Is the GNSS fusion is enabled
         * 
         */
        bool enable_GNSS_fusion = false;
        /**
         * @brief Distance necessary for initializing the transformation between cameras coordinate system and  GNSS coordinate system (north aligned)
         * 
         */
        float gnss_initialisation_distance = 5.0f;
        /**
         * @brief Value used by Fusion for ignoring high covariance input GNSS data
         * 
         */
        float gnss_ignore_threshold = 40.0f;
    };

    /**
    \enum POSITION_TYPE
    \ingroup Fusion_group
    \brief Change the type of outputed position (raw data or fusion data projected into zed camera)
    */
    enum class POSITION_TYPE{
        RAW=0, /*The output position will be the raw position data*/
        FUSION=1, /*The output position will be the fused position projected into the requested camera repository*/
        ///@cond SHOWHIDDEN 
        LAST
         ///@endcond
    };

    String /*@cond SHOWHIDDEN*/SL_CORE_EXPORT/*@endcond*/ toString(const POSITION_TYPE& position_type);

    inline ::std::ostream& operator<<(::std::ostream& os, const POSITION_TYPE& position_type) {
        return os << toString(position_type);
    }

    /**
    \class CameraMetrics
    \ingroup Fusion_group
    \brief Holds the metrics of a sender in the fusion process.
     */
    struct /*@cond SHOWHIDDEN*/SL_CORE_EXPORT/*@endcond*/ CameraMetrics {
        /**
         * @brief Default constructor
         */
        CameraMetrics();

        /**
          gives the fps of the received data
         */
        float received_fps;

        /**
          gives the latency (in second) of the received data
         */
        float received_latency;

        /**
         gives the latency (in second) after Fusion synchronization
         */
        float synced_latency;

        /**
          if no data present is set to false
         */
        bool is_present;

        /**
          percent of detection par image during the last second in %, a low values means few detections occurs lately
         */
        float ratio_detection;

        /**
          percent of detection par image during the last second in %, a low values means few detections occurs lately
         */
        float delta_ts;
    };

    /**
    \class FusionMetrics
    \ingroup Fusion_group
    \brief Holds the metrics of the fusion process.
     */
    struct /*@cond SHOWHIDDEN*/SL_CORE_EXPORT/*@endcond*/ FusionMetrics {
        /**
         * @brief Default constructor
         */
        FusionMetrics();

        /**
         * @brief reset the current metrics
         */
        void reset();

        /**
          mean number of camera that provides data during the past second
         */
        float mean_camera_fused;

        /**
          the standard deviation of the data timestamp fused, the lower the better
         */
        float mean_stdev_between_camera;

        /**
          the sender metrics
         */
        std::map<CameraIdentifier, CameraMetrics> camera_individual_stats;
    };

     /**
     * @brief Coordinates in ECEF format
     * 
     */
    class /*@cond SHOWHIDDEN*/SL_CORE_EXPORT/*@endcond*/ ECEF {
    public:
        /**
         * @brief x coordinate of ECEF
         * 
         */
        double x;
        /**
         * @brief y coordinate of ECEF
         * 
         */
        double y;
        /**
         * @brief z coordinate of ECEF
         * 
         */
        double z;
    };
    /**
     * @brief Coordinates in LatLng format
     * 
     */
    class /*@cond SHOWHIDDEN*/SL_CORE_EXPORT/*@endcond*/ LatLng {
    public:
        /**
         * @brief Get the coordinates in radians (default) or in degrees
         * 
         * @param latitude latitude coordinate
         * @param longitude longitude coordinate
         * @param altitude  altitude coordinate
         * @param in_radian should we express output in radians or in degrees
         */
        void getCoordinates(double & latitude, double & longitude, double & altitude, bool in_radian = true) const;
        /**
         * @brief Set the coordinates in radians (default) or in degrees
         * 
         * @param latitude latitude coordinate
         * @param longitude longitude coordinate
         * @param altitude altitude coordinate
         * @param in_radian is input are in radians or in degrees
         */
        void setCoordinates(double latitude, double longitude, double altitude, bool in_radian = true);
        /**
         * @brief Get the latitude coordinate
         * 
         * @param in_radian is the output should be in radian or degree
         * @return double 
         */
        double getLatitude(bool in_radian = true) const;
        /**
         * @brief Get the longitude coordinate
         * 
         * @param in_radian is the output should be in radian or degree
         * @return double 
         */
        double getLongitude(bool in_radian = true) const;
        /**
         * @brief Get the altitude coordinate 
         * 
         * @return double 
         */
        double getAltitude() const;
    protected:
        /**
         * @brief latitude coordinate
         * 
         */
        double latitude;
        /**
         * @brief longitude coordinate
         * 
         */
        double longitude;
        /**
         * @brief altitude coordinate
         * 
         */
        double altitude;
    };
    /**
     * @brief Coordinate in UTM format
     * 
     */
    class UTM {
    public:
        /**
         * @brief Northing coordinate
         * 
         */
        double northing;
        /**
         * @brief Easting coordinate
         * 
         */
        double easting;
        /**
         * @brief Gamma coordinate
         * 
         */
        double gamma;
        /**
         * @brief UTMZone of the coordinate
         * 
         */
        std::string UTMZone;
    };

    /**
    \class GeoConverter
    \ingroup Fusion_group
    \brief Purely static class for Geo functions
     */
    class /*@cond SHOWHIDDEN*/SL_CORE_EXPORT/*@endcond*/ GeoConverter {
    public:
        /**
         * @brief Convert ECEF coordinates to Lat/Long coordinates
         */
        static void ecef2latlng(sl::ECEF &in, sl::LatLng &out);

        /**
         * @brief Convert ECEF coordinates to UTM coordinates
         */
        static void ecef2utm(sl::ECEF &in, sl::UTM &out);

        /**
         * @brief Convert Lat/Long coordinates to ECEF coordinates
         */
        static void latlng2ecef(sl::LatLng &in, sl::ECEF &out);

        /**
         * @brief Convert Lat/Long coordinates to UTM coordinates
         */
        static void latlng2utm(sl::LatLng &in, sl::UTM &out);

        /**
         * @brief Convert UTM coordinates to ECEF coordinates
         */
        static void utm2ecef(sl::UTM &in, sl::ECEF &out);

        /**
         * @brief Convert UTM coordinates to Lat/Long coordinates
         */
        static void utm2latlng(sl::UTM &in, sl::LatLng &out);
    };

    /**
    \class GeoPose
    \ingroup Fusion_group
    \brief Holds Geo data
     */
    class /*@cond SHOWHIDDEN*/SL_CORE_EXPORT/*@endcond*/ GeoPose {
    public:
        /**
         * @brief Default constructor
         */
        GeoPose();

        /**
         * @brief Copy constructor
         */
        GeoPose(GeoPose const &geopose);

        /**
          the 4x4 Matrix defining the pose in ENU
         */
        sl::Transform pose_data;

        /**
          the pose covariance in ENU
         */
        float pose_covariance[36];

        /**
          the horizontal accuracy
         */
        double horizontal_accuracy;

        /**
          the vertical accuracy
         */
        double vertical_accuracy;

        /**
          the latitude, longitude, altitude
         */
        sl::LatLng latlng_coordinates;

        /**
          the heading
         */
        double heading;
    };

    /**
    \class GNSSData
    \ingroup Sensors_group
    \brief Contains all gnss data to be used for positional tracking as prior.
     */
    class  SL_CORE_EXPORT GNSSData { 
        public:
            /**
             * @brief Set the LatLng coordinates of GNSSData. The LatLng coordinates could be expressed in degrees or radians.
             * 
             * @param latitude latitude coordinate
             * @param longitude longitude coordinate
             * @param altitude altitude coordinate
             * @param is_radian is the inputs are expressed in radians or in degrees
             */
            void setCoordinates(double latitude, double longitude, double altitude, bool is_radian = true);
            /**
             * @brief Get the coordinates of GNSSData. The LatLng coordinates could be expressed in degrees or radians.
             * 
             * @param latitude latitude coordinate
             * @param longitude longitude coordinate
             * @param altitude altitude coordinate
             * @param is_radian should we express output in radians or in degrees
             */
            void getCoordinates(double &latitude, double &longitude, double &altitude, bool in_radian = true);
            
            /**
             * @brief sl::Timestamp in the PC clock
             */
            sl::Timestamp ts;
            /**
             * @brief Position covariance in meter must be expressed in ENU coordinate system.
             * For eph, epv GNSS sensors, set it as follow: {eph, 0, 0, 0, eph, 0, 0, 0, epv}
             * 
             */
            std::array<double, 9> position_covariance = {0.1 * 0.1, 0, 0, 0, 0.1 * 0.1, 0, 0, 0, 0.1 * 0.1};
            /**
             * @brief longitude standard deviation
             * 
             */
            double longitude_std;
            /**
             * @brief latitude standard deviation
             * 
             */
            double latitude_std;
            /**
             * @brief altitude standard deviation
             * 
             */
            double altitude_std;

        protected:
            double longitude;
            double latitude;
            double altitude;
    };

    /*@cond SHOWHIDDEN*/
    class FusionHandlerImp;
    /*@endcond*/

    /**
    \class Fusion
    \ingroup Fusion_group
    \brief Holds Fusion process data and functions
     */
    class /*@cond SHOWHIDDEN*/ SL_CORE_EXPORT /*@endcond*/ Fusion {
    public:
        /**
         * @brief Default constructor
         */
        Fusion();

        /**
         * @brief destructor
         */
        ~Fusion();

        /**
         * @brief initialize the fusion module with the requested parameters
         * \param init_parameters: the requested parameters
         * \return SUCCESS if it goes as it should, otherwise it returns an error code. 
         */
        FUSION_ERROR_CODE init(sl::InitFusionParameters init_parameters = InitFusionParameters());

        /**
         * @brief close will deactivate all the fusion modules and free internal data
         */
        void close();

        /**
         * @brief set the specified camera as a data provider
         * \param uuid: the requested camera identifier
         * \param param: the communication parameters to connect to the camera
         * \param pose: the World position of the camera, regarding the other camera of the setup
         * \return SUCCESS if it goes as it should, otherwise it returns an error code. 
         */
        FUSION_ERROR_CODE subscribe(CameraIdentifier uuid, CommunicationParameters param = CommunicationParameters(), sl::Transform pose = sl::Transform());

        /**
         * @brief updates the camera World pose
         * \param param: the communication parameters to connect to the camera
         * \param pose: the World position of the camera, regarding the other camera of the setup
         * \return SUCCESS if it goes as it should, otherwise it returns an error code. 
         */
        FUSION_ERROR_CODE updatePose(CameraIdentifier uuid, sl::Transform pose);

        /**
         * @brief get the metrics of the Fusion process, for the fused data as well as individual camera provider data
         * \param metrics (out): the process metrics
         * \return SUCCESS if it goes as it should, otherwise it returns an error code. 
         */
        FUSION_ERROR_CODE getProcessMetrics(FusionMetrics &metrics);

        /**
         * @brief returns the state of each connected data senders.
         * \return the individual state of each connected senders
         */
        std::map<CameraIdentifier, SENDER_ERROR_CODE> getSenderState();

        /**
         * @brief Runs the main function of the Fusion, this trigger the retrieve and sync of all connected senders and updates the enables modules
         * \return SUCCESS if it goes as it should, otherwise it returns an error code. 
         */
        FUSION_ERROR_CODE process();

        /**
         * @brief enables the body tracking module
         * \param params: the parameters to 
         * \return SUCCESS if it goes as it should, otherwise it returns an error code. 
         */
        FUSION_ERROR_CODE enableBodyTracking(BodyTrackingFusionParameters params = BodyTrackingFusionParameters());

        /**
         * @brief retrieves the body data, can be the fused data (default), or the raw data provided by a specific sender
         * \param objs: the body data
         * \param parameters: the runtime parameters
         * \param uuid: if set to a sender serial number (different from 0), this will retrieve the raw data provided by this sender
         * \return SUCCESS if it goes as it should, otherwise it returns an error code. 
         */
        FUSION_ERROR_CODE retrieveBodies(sl::Bodies &objs, BodyTrackingFusionRuntimeParameters parameters = BodyTrackingFusionRuntimeParameters(), CameraIdentifier uuid = CameraIdentifier());

        /**
         * @brief disable the body tracking module
         */
        void disableBodyTracking();

        /**
         * @brief enables positional tracking module
         * \return SUCCESS if it goes as it should, otherwise it returns an error code. 
         */
        FUSION_ERROR_CODE enablePositionalTracking(PositionalTrackingFusionParameters parameters = PositionalTrackingFusionParameters());

        /**
         * @brief Get the Fused Position of the camera system
         * \param camera_pose will contain the camera pose in world position (world position is given by the calibration of the cameras system)
         * \param reference_frame defines the reference from which you want the pose to be expressed. Default : \ref REFERENCE_FRAME "REFERENCE_FRAME::WORLD".
         * \param uuid: if set to a sender serial number (different from 0), this will retrieve the raw data provided by this sender
         * \param position_type: select if the position should the fused position re-projected in the camera with uuid or if the position should be the raw position (without fusion) of camera with uui
         * \return POSITIONAL_TRACKING_STATE is the current state of the tracking process
         */
        POSITIONAL_TRACKING_STATE getPosition(Pose &camera_pose, sl::REFERENCE_FRAME reference_frame = REFERENCE_FRAME::WORLD, CameraIdentifier uuid = CameraIdentifier(), POSITION_TYPE position_type = POSITION_TYPE::FUSION);

        /**
         * @brief ingest GNSS data from an external sensor into the fusion module
         * \param _gnss_data: the current GNSS data to combine with the current positional tracking data
         */
        void ingestGNSSData(sl::GNSSData gnss_data);

        /**
         * @brief returns the current GNSS data
         * \param out [out]: the current GNSS data 
         * \return POSITIONAL_TRACKING_STATE is the current state of the tracking process
         */
        POSITIONAL_TRACKING_STATE getCurrentGNSSData(sl::GNSSData &out);

        /**
         * @brief returns the current GeoPose
         * \param pose [out]: the current GeoPose
         * \return POSITIONAL_TRACKING_STATE is the current state of the tracking process
         */
        POSITIONAL_TRACKING_STATE getGeoPose(sl::GeoPose &pose);

        /**
         * @brief Convert latitude / longitude into position in sl::Fusion coordinate system.
         * \param in: the current GeoPose
         * \param out [out]: the current GeoPose
         * \return POSITIONAL_TRACKING_STATE is the current state of the tracking process
         */
        POSITIONAL_TRACKING_STATE Geo2Camera(sl::LatLng &in, sl::Pose &out);

        /**
         * @brief Convert a position in sl::Fusion coordinate system in real world coordinate. 
         * \param pose [out]: the current GeoPose
         * \return POSITIONAL_TRACKING_STATE is the current state of the tracking process
         */
        POSITIONAL_TRACKING_STATE Camera2Geo(sl::Pose const &in, sl::GeoPose &out);

        /**
         * @brief disable the positional tracking 
         */
        void disablePositionalTracking();

    private:
        std::unique_ptr<FusionHandlerImp> pimpl;
    };
}

#endif /* __FUSION_HPP__ */
